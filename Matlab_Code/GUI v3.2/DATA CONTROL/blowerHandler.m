function blowerStates = blowerHandler( handles )
% Author Dan Wheeler
% November 20, 2012
% ESE 519 EnRoute 2.0 


blowerStates = handles.blowerStates;

%
% DISABLE SLIDERS FOR NON-MANUAL CONTROL
%
if ~get(handles.checkbox1,'Value')                                         % If you are not allowing manual control ...
    set(handles.slider1_HVAC,'Enable','off');                              % Disable all sliders and radio buttons
    %set(handles.rb_HVAC_return_on,'Enable','off');
    %set(handles.rb_HVAC_return_off,'Enable','off');
    %set(handles.rb_HVAC_cooler_on,'Enable','off');
    %set(handles.rb_HVAC_cooler_off,'Enable','off');
    set(handles.rb_HVAC_supply_on,'Enable','off');
    set(handles.rb_HVAC_supply_off,'Enable','off');
else                                                                       % ... else
    set(handles.slider1_HVAC,'Enable','on');                              % Enable all sliders and radio buttons
    set(handles.rb_HVAC_return_on,'Enable','on');
    set(handles.rb_HVAC_return_off,'Enable','on');
    set(handles.rb_HVAC_cooler_on,'Enable','on');
    set(handles.rb_HVAC_cooler_off,'Enable','on');
    set(handles.rb_HVAC_supply_on,'Enable','on');
    set(handles.rb_HVAC_supply_on,'Enable','on');
end

%
% READ FROM SLIDER - IF MANUAL CONTROL ENABLED
%
if get(handles.checkbox1,'Value') 
	blowerStates(1) = get(handles.slider1_HVAC,'Value');                   % ... set blower off slider control
end

% 
% UPDATE BINARY BLOWER STATES
%
blowerStates(2) = get(handles.rb_HVAC_return_on,'Value');
blowerStates(3) = get(handles.rb_HVAC_cooler_on,'Value');

%
% UPDATE SLIDERS
%
if blowerStates(1) >= 60
    set(handles.slider1_HVAC,'Value',blowerStates(1));
else
    set(handles.slider1_HVAC,'Value',60);
end


end

