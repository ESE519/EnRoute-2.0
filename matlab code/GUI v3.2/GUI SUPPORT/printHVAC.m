function printHVAC( handles , data , tempUnits )
% Author Dan Wheeler
% November 10, 2012
% ESE 519 EnRoute 2.0 
% PRINTHVAC prints data to the hvac tab of EnRoute2.0 GUI 
%
%   INPUTS:  
%       handles     =   Handle to gui data
%       data        =   Struct containing plotting data
%

%flowYLimits = [-1 15];
flowYLimits = [-1 50];
speedYLimits = [-1 8];
valveYLimits = [-5 95];
blowerLimits = [-5 105];
currentLimits = [-1 10];
powerLimits = [-1 15];

if tempUnits == 'F'
    tempYLimits = [55 85];
else
    tempYLimits = [10 45];
end

%
% HVAC GENERAL
%
if get(handles.rb_HVAC_flow,'Value')
    printAxis(handles.axes1_HVAC,data.time,data.flow.HVAC,'time s','flow cfm',flowYLimits,1);
elseif get(handles.rb_Amb_temp,'Value')
    printAxis(handles.axes1_HVAC,data.time,data.filterTemp.Amb,'time s','temp o',tempYLimits,1);
elseif get(handles.rb_HVAC_temp,'Value')
    printAxis(handles.axes1_HVAC,data.time,data.filterTemp.HVAC,'time s','temp o',tempYLimits,1);
elseif get(handles.rb_HVAC_blowerspeed,'Value')
    printAxis(handles.axes1_HVAC,data.time,data.blower.supply,'time s','blower speed %',blowerLimits,1);
end

%
% HVAC VALVES
%
if get(handles.rb_HVAC_exhaust,'Value')
    printAxis(handles.axes2_HVAC,data.time,data.valve.exhaust,'time s','angle o',valveYLimits,1);
elseif get(handles.rb_HVAC_inlet,'Value')
    printAxis(handles.axes2_HVAC,data.time,data.valve.inlet,'time s','angle o',valveYLimits,1);
end

%
% HVAC POWER
%
if get(handles.rb_blower_current,'Value')
    printAxis(handles.axes3_HVAC,data.time,data.current.blower,'time s','current A',currentLimits,1);
elseif get(handles.rb_blower_power,'Value')
    printAxis(handles.axes3_HVAC,data.time,data.power.blower,'time s','power W',powerLimits,1);
elseif get(handles.rb_heater_current,'Value')
    printAxis(handles.axes3_HVAC,data.time,data.current.heater,'time s','current A',currentLimits,1);
else
    printAxis(handles.axes3_HVAC,data.time,data.power.heater,'time s','power W',powerLimits,1);
end


end

