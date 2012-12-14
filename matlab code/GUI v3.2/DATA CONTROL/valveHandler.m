function valveAngles = valveHandler( handles , prevAngles )
% Author Dan Wheeler
% November 13, 2012
% ESE 519 EnRoute 2.0 
% VALVEHANDLER updates all sliders to match from different "tabs" 
%
%   INPUTS:  
%       handles     =   Handle to gui data
%       valveAngles =   Vector with valve angles (1,2,3,4)
% 

%
% DISABLE SLIDERS FOR NON-MANUAL CONTROL
%
if ~get(handles.checkbox1,'Value')                                         % If you are not allowing manual control ...
    set(handles.slider1,'Enable','off');                                   % Disable all sliders
    set(handles.slider2,'Enable','off');
    set(handles.slider3,'Enable','off');
    set(handles.slider4,'Enable','off');
    set(handles.slider1_zone1,'Enable','off');
    set(handles.slider2_zone2,'Enable','off');
    set(handles.slider3_zone3,'Enable','off');
    set(handles.slider4_zone4,'Enable','off');
else                                                                       % ... else
    set(handles.slider1,'Enable','on');                                    % Enable all sliders
    set(handles.slider2,'Enable','on');
    set(handles.slider3,'Enable','on');
    set(handles.slider4,'Enable','on');
    set(handles.slider1_zone1,'Enable','on');
    set(handles.slider2_zone2,'Enable','on');
    set(handles.slider3_zone3,'Enable','on');
    set(handles.slider4_zone4,'Enable','on');
end

%
% SET SLIDER VALUES FOR 1-4
%
if get(handles.checkbox1,'Value') 
    if get(handles.tab2,'Value')                                               % Zone 1 Overview
        valveAngles = [ get(handles.slider1_zone1,'Value') get(handles.slider2,'Value') get(handles.slider3,'Value') get(handles.slider4,'Value') ];    
    elseif get(handles.tab3,'Value')
        valveAngles = [ get(handles.slider1,'Value') get(handles.slider2_zone2,'Value') get(handles.slider3,'Value') get(handles.slider4,'Value') ];    
    elseif get(handles.tab4,'Value')
        valveAngles = [ get(handles.slider1,'Value') get(handles.slider2,'Value') get(handles.slider3_zone3,'Value') get(handles.slider4,'Value') ];   
    elseif get(handles.tab5,'Value')
        valveAngles = [ get(handles.slider1,'Value') get(handles.slider2,'Value') get(handles.slider3,'Value') get(handles.slider4_zone4,'Value') ]; 
    else
        valveAngles = [ get(handles.slider1,'Value') get(handles.slider2,'Value') get(handles.slider3,'Value') get(handles.slider4,'Value') ];
    end
else
    valveAngles = prevAngles(:,1:4);
end

%
% SET SLIDER VALUES FOR 5-6
%
if get(handles.rb_HVAC_exhaust,'Value')
    valveAngles = [ valveAngles , get(handles.slider2_HVAC,'Value') , prevAngles(6) ];
    set(handles.slider2_HVAC,'Value',valveAngles(5));
elseif get(handles.rb_HVAC_inlet,'Value')
    valveAngles = [ valveAngles , prevAngles(5) , get(handles.slider2_HVAC,'Value') ];
    set(handles.slider2_HVAC,'Value',valveAngles(6));
end

%
% UPDATE SLIDERS
%
set(handles.slider1,'Value',valveAngles(1));
set(handles.slider2,'Value',valveAngles(2));
set(handles.slider3,'Value',valveAngles(3));
set(handles.slider4,'Value',valveAngles(4));
set(handles.slider1_zone1,'Value',valveAngles(1));
set(handles.slider2_zone2,'Value',valveAngles(2));
set(handles.slider3_zone3,'Value',valveAngles(3));
set(handles.slider4_zone4,'Value',valveAngles(4));

end

