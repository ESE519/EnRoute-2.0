function initControl( handles )


%% ZONE CONTROL

%
% ON_OFF CONTROL
%

% Load set points from text fields
high_sp = { get(handles.text_1_high_sp,'String') , get(handles.text_2_high_sp,'String') , get(handles.text_3_high_sp,'String') , get(handles.text_4_high_sp,'String') };
low_sp = { get(handles.text_1_low_sp,'String') , get(handles.text_2_low_sp,'String') , get(handles.text_3_low_sp,'String') , get(handles.text_4_low_sp,'String') };

if get(handles.rb_temp_units_f,'Value')
    for i=1:numel(high_sp)
        high_sp{i} = num2str( (5/9)*( str2num( high_sp{i} ) - 32 ) );
        low_sp{i} = num2str( (5/9)*( str2num( low_sp{i} ) - 32 ) );
    end
end

set_param('ON_OFF/Relay_1','OnSwitchValue', high_sp{1} );
set_param('ON_OFF/Relay_1','OffSwitchValue', low_sp{1} );
set_param('ON_OFF/Relay_2','OnSwitchValue', high_sp{2} );
set_param('ON_OFF/Relay_2','OffSwitchValue', low_sp{2} );
set_param('ON_OFF/Relay_3','OnSwitchValue', high_sp{3} );
set_param('ON_OFF/Relay_3','OffSwitchValue', low_sp{3} );
set_param('ON_OFF/Relay_4','OnSwitchValue', high_sp{4} );
set_param('ON_OFF/Relay_4','OffSwitchValue', low_sp{4} );

set_param('ON_OFF_LAZY/Low Set Points','Value', 'low_sp')
set_param('ON_OFF_LAZY/High Set Points','Value', 'high_sp')
set_param('ON_OFF_LAZY/Max Zones Allowable','Value', '2')

set_param('K_LAZY/Low Set Points','Value', 'low_sp')
set_param('K_LAZY/High Set Points','Value', 'high_sp')
set_param('K_LAZY/Max Power Allowable','Value', '8')

high_sp = [ str2num(high_sp{1}) , str2num(high_sp{2}) , str2num(high_sp{3}) , str2num(high_sp{4}) ];
low_sp = [ str2num(low_sp{1}) , str2num(low_sp{2}) , str2num(low_sp{3}) , str2num(low_sp{4}) ];
assignin('base','low_sp',low_sp);
assignin('base','high_sp',high_sp);


% COOLING
if get(handles.rb_cool,'Value')
    % Load ON/OFF values - Turn on at high point ( SwitchOnPoint > SwitchOffPoint )
    set_param('ON_OFF/Relay_1','OnOutputValue','0');
    set_param('ON_OFF/Relay_1','OffOutputValue','90');
    set_param('ON_OFF/Relay_2','OnOutputValue','0');
    set_param('ON_OFF/Relay_2','OffOutputValue','90');
    set_param('ON_OFF/Relay_3','OnOutputValue','0');
    set_param('ON_OFF/Relay_3','OffOutputValue','90');
    set_param('ON_OFF/Relay_4','OnOutputValue','0');
    set_param('ON_OFF/Relay_4','OffOutputValue','90');
    
    set_param('ON_OFF_LAZY/Hot or Cold','Value','0');
    set_param('K_LAZY/Hot or Cold','Value','0');
% HEATING
else
    % Load ON/OFF values - Turn off at high point ( SwitchOnPoint > SwitchOffPoint )
    set_param('ON_OFF/Relay_1','OnOutputValue','90');
    set_param('ON_OFF/Relay_1','OffOutputValue','9');
    set_param('ON_OFF/Relay_2','OnOutputValue','90');
    set_param('ON_OFF/Relay_2','OffOutputValue','0');
    set_param('ON_OFF/Relay_3','OnOutputValue','90');
    set_param('ON_OFF/Relay_3','OffOutputValue','0');
    set_param('ON_OFF/Relay_4','OnOutputValue','90');
    set_param('ON_OFF/Relay_4','OffOutputValue','0');
    
    set_param('ON_OFF_LAZY/Hot or Cold','Value','1');
    set_param('K_LAZY/Hot or Cold','Value','1');
end
    

%% HVAC CONTROL

%
% VALVE PROPORTIONAL CONTROL
%

% All initializers set in model file


end

