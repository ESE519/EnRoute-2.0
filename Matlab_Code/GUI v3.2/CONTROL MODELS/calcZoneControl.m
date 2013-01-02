function  [valveOutputs finalState] = calcZoneControl( mdl , tempInputs , tStart , tStep , initState )

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
p.ExternalInput = 'UT';
p.SaveFinalState = 'on';
p.SaveCompleteFinalSimState = 'on';
p.FinalStateName = 'xFinal';
p.SaveOutput = 'on';
p.SaveTime = 'off';
p.OutputSaveName = 'yOut';

% u1 = tempInputs(1);
% u2 = tempInputs(2);
% u3 = tempInputs(3);
% u4 = tempInputs(4);
% t = tStart;
UT = [tStart , tempInputs];
assignin('base','UT',UT)

% assignin('base','t',t);
% assignin('base','u1',u1);
% assignin('base','u2',u2);
% assignin('base','u3',u3);
% assignin('base','u4',u4);

SimOut = sim(mdl, p);
temp = SimOut.find('yOut');
valveOutputs = [temp(1,1) temp(1,2) temp(1,3) temp(1,4)];

finalState = SimOut.find('xFinal');

end

