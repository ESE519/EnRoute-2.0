close all

time = data.time;
power = data.blower.supply;

figure(1)
plot(time,power);
hold on
plot([0 time( numel(time) )],[82.34 82.34],'r')
%ylim([78 84])
legend('power','limit')
xlabel('time [s]','FontSize',16)
ylabel('blower power [%]','FontSize',16)
title('Blower Power vs. Time ON-OFF','FontSize',20);

figure(2)
plot(time,data.filterTemp.z1)
hold on
plot([0 time( numel(time) )],[23 23],'r')
plot([0 time( numel(time) )],[24 24],'r')
ylim([21 25])
legend('temp','limits')
xlabel('time [s]','FontSize',16)
ylabel('Temp [C]','FontSize',16)
title('Room 1 Temp vs. Time ON-OFF Scheduler','FontSize',20);

%%

figure(3)
plot(time,data.filterTemp.z2)
hold on
plot([0 time( numel(time) )],[23 23],'r')
plot([0 time( numel(time) )],[24 24],'r')
ylim([21 25])
legend('temp','limits')
xlabel('time [s]','FontSize',16)
ylabel('Temp [C]','FontSize',16)
title('Room 2 Temp vs. Time K-Lazy Scheduler','FontSize',20);

figure(4)
plot(time,data.filterTemp.z3)
hold on
plot([0 time( numel(time) )],[21 21],'r')
plot([0 time( numel(time) )],[22 22],'r')
ylim([18 23])
legend('temp','limits')
xlabel('time [s]','FontSize',16)
ylabel('Temp [C]','FontSize',16)
title('Room 3 Temp vs. Time K-Lazy Scheduler','FontSize',20);

figure(5)
plot(time,data.filterTemp.z4)
hold on
plot([0 time( numel(time) )],[21 21],'r')
plot([0 time( numel(time) )],[20 20],'r')
ylim([18 23])
legend('temp','limits')
xlabel('time [s]','FontSize',16)
ylabel('Temp [C]','FontSize',16)
title('Room 4 Temp vs. Time K-Lazy Scheduler','FontSize',20);

figure(6)
plot(time,data.valve.z1)
ylim([-1 91])
hold on
xlabel('time [s]','FontSize',16)
ylabel('Valve [o]','FontSize',16)
title('Room 1 Valve vs. Time K-Lazy Scheduler','FontSize',20);

figure(7)
plot(time,data.valve.z2)
ylim([-1 91])
hold on
xlabel('time [s]','FontSize',16)
ylabel('Valve [o]','FontSize',16)
title('Room 2 Valve vs. Time K-Lazy Scheduler','FontSize',20);

figure(8)
plot(time,data.valve.z3)
ylim([-1 91])
hold on
xlabel('time [s]','FontSize',16)
ylabel('Valve [o]','FontSize',16)
title('Room 3 Valve vs. Time K-Lazy Scheduler','FontSize',20);

figure(9)
plot(time,data.valve.z4)
ylim([-1 91])
hold on
xlabel('time [s]','FontSize',16)
ylabel('Valve [o]','FontSize',16)
title('Room 4 Valve vs. Time K-Lazy Scheduler','FontSize',20);

figure(10)
plot(time,data.filterTemp.Amb)
hold on
xlabel('time [s]','FontSize',16)
ylabel('temp [C]','FontSize',16)
title('Ambient Temp vs. Time K-Lazy Scheduler','FontSize',20);



