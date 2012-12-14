function printZone4( handles , data , tempUnits)
% Author Dan Wheeler
% November 10, 2012
% ESE 519 EnRoute 2.0 
% PRINTZONE4 prints data to the zone4 tab of EnRoute2.0 GUI 
%
%   INPUTS:  
%       handles     =   Handle to gui data
%       data        =   Struct containing plotting data
%                       *Time
%                       *Temp
%                       *Flow
%                       *Speed
%                       *Servo
%

flowYLimits = [-1 8];
speedYLimits = [-1 8];
valveYLimits = [-5 95];

if tempUnits == 'F'
    tempYLimits = [55 85];
else
    tempYLimits = [10 30];
end

%
% ZONE 1
%
if get(handles.rb_3_flow_zone3,'Value')
    printAxis(handles.axes1_zone3,data.time,data.flow.z3,'time s','flow cfm',flowYLimits,1);
    printAxis(handles.axes2_zone3,data.time,data.speed.z3,'time s','speed m/s',speedYLimits,1);
    printAxis(handles.axes3_zone3,data.time,data.filterTemp.z3,'time s','temp C',tempYLimits,1);
    %printAxis(handles.axes3_zone3,data.time,data.filterTemp.z3,tempYLimits,'r');
    printAxis(handles.axes4_zone3,data.time,data.valve.z3,'time s','valve angle o',valveYLimits,1);
elseif get(handles.rb_3_speed_zone3,'Value')
    printAxis(handles.axes4_zone3,data.time,data.flow.z3,'time s','flow cfm',flowYLimits,1);
    printAxis(handles.axes1_zone3,data.time,data.speed.z3,'time s','speed m/s',speedYLimits,1);
    printAxis(handles.axes2_zone3,data.time,data.filterTemp.z3,'time s','temp C',tempYLimits,1);
    %printAxis(handles.axes2_zone3,data.time,data.filterTemp.z3,tempYLimits,'r');
    printAxis(handles.axes3_zone3,data.time,data.valve.z3,'time s','valve angle o',valveYLimits,1);
elseif get(handles.rb_3_temp_zone3,'Value')
    printAxis(handles.axes3_zone3,data.time,data.flow.z3,'time s','flow cfm',flowYLimits,1);
    printAxis(handles.axes4_zone3,data.time,data.speed.z3,'time s','speed m/s',speedYLimits,1);
    printAxis(handles.axes1_zone3,data.time,data.filterTemp.z3,'time s','temp C',tempYLimits,1);
    %printAxis(handles.axes1_zone3,data.time,data.filterTemp.z3,tempYLimits,'r');
    printAxis(handles.axes2_zone3,data.time,data.valve.z3,'time s','valve angle o',valveYLimits,1);
else
    printAxis(handles.axes2_zone3,data.time,data.flow.z3,'time s','flow cfm',flowYLimits,1);
    printAxis(handles.axes3_zone3,data.time,data.speed.z3,'time s','speed m/s',speedYLimits,1);
    printAxis(handles.axes4_zone3,data.time,data.filterTemp.z3,'time s','temp C',tempYLimits,1);
    %printAxis(handles.axes4_zone3,data.time,data.filterTemp.z3,tempYLimits,'r');
    printAxis(handles.axes1_zone3,data.time,data.valve.z3,'time s','valve angle o',valveYLimits,1);
end

end

