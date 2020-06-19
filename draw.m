style = ['k-*'; 'k-o'; 'k-s'; 'k-d'];
for i = 1 : 4
    file_name = ['./bin/result_', mat2str(i*2), '.txt'];
    file = fopen(file_name,'rt');
    data = textscan(file, '%f %f %f', 'Delimiter', ' ');
    [linkrate, throughput, latency] = deal(data{:});
    fclose(file);
    handle = plot(linkrate, throughput, style(i,:), 'LineWidth', 1.5);
    % handle = plot(linkrate, latency, style(i,:), 'LineWidth', 1.5);
    hold on
    grid on
end

h = legend('$ 2d $', '$ 4d $', '$ 6d $', '$ 8d $');
set(h, 'Location', 'NorthWest', 'Interpreter', 'latex');
set(gca, 'YLim', [0 0.5]);
xlabel('Packet injection rate [packet/cycle/node]','fontsize',10);
ylabel('Throughput [flits/cycle/node]','fontsize',10);
% ylabel('Average packet delay [cycles]','fontsize',10);
