function  [blowerOutputs finalState] = calcHVACControl( mdl , inputs , tStart , tStep , initState )
%
% inputs = [v1 v2 v3 v4 f1 f2 f3 f4]

%
% SET TIME VARIABLES
%
tStop = tStart + tStep;
p.StartTime = num2str(tStart);
p.StopTime = num2str(tStop);
p.FixedStep = num2str(tStep);

%
% INITIAL STATE
%
if isempty(initState)
    p.LoadInitialState = 'off';
else
    p.LoadInitialState = 'on';
    assignin('base','xInitial',initState);
end
p.InitialState = 'xInitial';

p.LoadExternalInput = 'on';
p.ExternalInput = '[t,u1,u2,u3,u4,u5,u6,u7,u8]';
p.SaveFinalState = 'on';
p.SaveCompleteFinalSimState = 'on';
p.FinalStateName = 'xFinal';
p.SaveOutput = 'on';
p.SaveTime = 'off';
p.OutputSaveName = 'yOut';

u1 = inputs(1);
u2 = inputs(2);
u3 = inputs(3);
u4 = inputs(4);
u5 = inputs(5);
u6 = inputs(6);
u7 = inputs(7);
u8 = inputs(8);
t = tStart;

assignin('base','t',t);
assignin('base','u1',u1);
assignin('base','u2',u2);
assignin('base','u3',u3);
assignin('base','u4',u4);
assignin('base','u5',u5);
assignin('base','u6',u6);
assignin('base','u7',u7);
assignin('base','u8',u8);

SimOut = sim(mdl, p);
temp = SimOut.find('yOut');
blowerOutputs = temp(1);

finalState = SimOut.find('xFinal');

end

