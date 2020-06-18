#include <cmath>

#include "common.h"

int GENERATETYPE;  //用于选择linkrate的增长方式
int totalcircle;  //程序总的运行周期
int knode;        //维数

int getsize(vector<Message*>* mess);

int main() {
  for (int knode = 2; knode <= 8; knode++) {
    int threshold = 800;
    Allrouting* rout = NULL;
    totalcircle = 100000;
    Hypercube* hcube = NULL;
    Event* s = NULL;
    int r1, r2;

    int r1buffer[5] = {1, 2, 1, 2, 2};  //虚拟信道1缓存大小，以message个数为基本单位
    int r2buffer[5] = {2, 1, 0, 1, 1};  //虚拟信道2缓存大小，若无虚拟通道不使用r2

    for (int round = 2; round < 3; round++) {
      char filename[16]; 
      sprintf(filename, "result_%d.txt", knode);
      ofstream out = ofstream(filename);
      float linkrate = 0;
      double max = 0;

      /************************************************************************************

                                              start simulate

***********************************************************************************/
      cout << "---------- " << knode <<  "d hypercube ----------" << endl;
      // linkrate控制消息产生速率
      for (linkrate = 0.01; linkrate < 1;) {
        r1 = r1buffer[round] * MESSLENGTH;  //以flit个数为基本单位
        r2 = r2buffer[round] * MESSLENGTH;
        hcube = new Hypercube(knode, r1, r2);  //初始化网络结构

        rout = new Routing(hcube);
        s = new Event(rout);

        float msgpercir =
            (float)(linkrate * 2 * 2 * pow(2, knode-1) /
                    (MESSLENGTH *
                     10));  //每个周期每个节点产生的message数，还要除以10是因为allvecmess有10个元素
        // hypercube:
        // saturationRate = 2 * b * Bc / N
        //                = (double) (2 * 2 * pow(2, knode-1)) / (double)pow(2, knode);
        // msgpercir = linkrate * saturationRate * pow(2, knode)

        vector<Message*> allvecmess[10];
        float k = 0;
        int allmess = 0;

        /************************************************************************************

                                        genarate message

  ***********************************************************************************/
        //执行totalcircle个周期，getsize(allvecmess) <
        // threshold只是自己加的限制条件，可以有也可以删除，具体的threshold和totalcircle值也可以在前面修改
        for (int i = 0; i < totalcircle && getsize(allvecmess) < threshold; i++) {
          vector<Message*>& vecmess = allvecmess[i % 10];
          for (k += msgpercir; k > 0; k--) {
            allmess++;  //总的产生消息数加一
            vecmess.push_back(
                s->genMes());  //产生消息放入	allvecmess的某个元素中
          }

          /************************************************************************************

                                          release link

    ***********************************************************************************/

          for (vector<Message*>::iterator it = vecmess.begin();
               it != vecmess.end(); it++) {
            /* if the tail of a message shifts ,
            the physical link the message  occupied should release.
              */

            if ((*it)->releaselink == true) {
              assert((*it)->routpath[MESSLENGTH - 1].buff->linkused);
              (*it)->routpath[MESSLENGTH - 1].buff->linkused =
                  false;  //释放链路
              (*it)->releaselink = false;
            }
          }

          /************************************************************************************

                                          forward message

    ***********************************************************************************/
          for (vector<Message*>::iterator it = vecmess.begin();
               it != vecmess.end();) {
            if ((*it)->active == false) {  // when a message arrive at its
                                           // destination, it is not active
              delete (*it);
              it = vecmess.erase(it);  //消息到达目的节点，将它从vecmess中删除
            } else
              s->forwardMes(*(*it++));  //调用Routing.cpp中函数转发消息
          }
        }

        /*****************************************************************************

                                        output results
          ****************************************************************************/

        int size = getsize(allvecmess);

        // s->totalcir/s->messarrive 平均延迟的计算公式；linkrate * ((float)
        // s->messarrive / allmess)吞吐量的计算公式
        cout << "linkrate:" << linkrate << "    arrive:  " << s->messarrive
             << "    in the network : " << size << endl
             << "average latency: " << (s->totalcir / s->messarrive)
             << "  nomalized accepted traffic: "
             << linkrate * ((float)s->messarrive / allmess) << endl
             << endl;

        out << linkrate * ((float)s->messarrive / allmess) << " "
            << (s->totalcir / s->messarrive) << endl;

        /************************************************************************************

                                           whether arrive at saturation point

  ***********************************************************************************/
        if (linkrate * ((float)s->messarrive / allmess) > max &&
            ((linkrate * ((float)s->messarrive / allmess) - max) / max) >
                0.01 &&
            getsize(allvecmess) < threshold)
          max = linkrate * ((float)s->messarrive / allmess);

        else {
          cout << "Saturation point, drain......." << endl;
          drain(allvecmess, hcube, s);
          int size = 0;
          for (int j = 0; j < 10; j++) {
            if (!allvecmess[j].empty()) {
              size += allvecmess[j].size();
            }
          }
          cout << "in the network:      " << size << endl;
          cout << "max:" << max << endl << endl;
          // outtotest(allvecmess, hcube);
          break;
        }

        /************************************************************************************
                    clean
  *******************************************************************************************/

        for (int m = 0; m < 10; m++) {
          for (vector<Message*>::iterator it = allvecmess[m].begin();
               it != allvecmess[m].end(); it++)
            delete (*it);
        }
        delete rout;
        delete hcube;
        delete s;

        if (linkrate < 0.5) linkrate += 0.05;
        else linkrate += 0.02;
      }  // each linkrate end
    }    // round end
  }
  return 0;
}
