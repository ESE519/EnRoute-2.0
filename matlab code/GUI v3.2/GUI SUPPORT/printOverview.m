function printOverview( handles , data , tempUnits)
% Author Dan Wheeler
% November 10, 2012
% ESE 519 EnRoute 2.0 
% PRINTOVERVIEW prints data to the overview tab of EnRoute2.0 GUI 
%
%   INPUTS:  
%       handles     =   Handle to gui data
%       data        =   Struct containing plotting data
%                       *Time
%                       *Temp
%                       *Flow
%                       *Speed
%                       *Servo
%       tempUnits   =   'C' or 'F'
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
if get(handles.rb_1_flow,'Value')
    printAxis(handles.axes1,data.time,data.flow.z1,'time s','flow cfm',flowYLimits,1);
elseif get(handles.rb_1_speed,'Value')
    printAxis(handles.axes1,data.time,data.speed.z1,'time s','speed m/s',speedYLimits,1);
elseif get(handles.rb_1_temp,'Value')
    printAxis(handles.axes1,data.time,data.filterTemp.z1,'time s','temp C',tempYLimits,1);
else
    printAxis(handles.axes1,data.time,data.valve.z1,'time s','valve angle o',valveYLimits,1);
end

%
% ZONE 2
%
if get(handles.rb_2_flow,'Value')
    printAxis(handles.axes2,data.time,data.flow.z2,'time s','flow cfm',flowYLimits,1);
elseif get(handles.rb_2_speed,'Value')
    printAxis(handles.axes2,data.time,data.speed.z2,'time s','speed m/s',speedYLimits,1);
elseif get(handles.rb_2_temp,'Value')
    printAxis(handles.axes2,data.time,data.filterTemp.z2,'time s','temp C',tempYLimits,1);
else
    printAxis(handles.axes2,data.time,data.valve.z2,'time s','valve angle o',valveYLimits,1);
end

% 
% ZONE 3
%
if get(handles.rb_3_flow,'Value')
    printAxis(handles.axes3,data.time,data.flow.z3,'time s','flow cfm',flowYLimits,1);
elseif get(handles.rb_3_speed,'Value')
    printAxis(handles.axes3,data.time,data.speed.z3,'time s','speed m/s',speedYLimits,1);
elseif get(handles.rb_3_temp,'Value')
    printAxis(handles.axes3,data.time,data.filterTemp.z3,'time s','temp C',tempYLimits,1);
else
    printAxis(handles.axes3,data.time,data.valve.z3,'time s','valve angle o',valveYLimits,1);
end

%
% ZONE 4
%
if get(handles.rb_4_flow,'Value')
    printAxis(handles.axes4,data.time,data.flow.z4,'time s','flow cfm',flowYLimits,1);
elseif get(handles.rb_4_speed,'Value')
    printAxis(handles.axes4,data.time,data.speed.z4,'time s','speed m/s',speedYLimits,1);
elseif get(handles.rb_4_temp,'Value')
    printAxis(handles.axes4,data.time,data.filterTemp.z4,'time s','temp C',tempYLimits,1);
else
    printAxis(handles.axes4,data.time,data.valve.z4,'time s','valve angle o',valveYLimits,1);
end


end

