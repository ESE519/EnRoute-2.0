function updateControlModels( handles )

out = dir('CONTROL MODELS/ZONE/*.mdl');

for i = 1:size(out,1)
    mdl{i} = out(i).name;
end

set(handles.menuZoneControl,'String',mdl);

clear mdl out

out = dir('CONTROL MODELS/HVAC/*.mdl');

for i = 1:size(out,1)
    mdl{i} = out(i).name;
end

set(handles.menuBlowerControl,'String',mdl);

end

