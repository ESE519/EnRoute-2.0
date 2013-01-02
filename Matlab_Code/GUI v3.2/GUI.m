%
% MAIN GUI FUNCTION - DO NOT EDIT
%
function varargout = GUI(varargin)
% GUI MATLAB code for GUI.fig
%      GUI, by itself, creates a new GUI or raises the existing
%      singleton*.
%
%      H = GUI returns the handle to a new GUI or the handle to
%      the existing singleton*.
%
%      GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GUI.M with the given input arguments.
%
%      GUI('Property','Value',...) creates a new GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help GUI

% Last Modified by GUIDE v2.5 03-Dec-2012 21:20:58

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @GUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
%
% GUI INIT FUNCTION
%
function GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to GUI (see VARARGIN)

% Choose default command line output for GUI
handles.output = hObject;

% Tab Handles
handles.tabHandles = [  handles.pannel1                                    % Overview tab
                        handles.pannel2                                    % Zone 1 tab
                        handles.pannel3                                    % Zone 2 tab
                        handles.pannel4                                    % Zone 3 tab
                        handles.pannel5                                    % Zone 4 tab
                        handles.pannel6                                    % HVAC tab
                        handles.pannel7                                    % Controls tab
                        handles.tab1 
                        handles.tab2 
                        handles.tab3 
                        handles.tab4 
                        handles.tab5 
                        handles.tab6 
                        handles.tab7        ]';
tabHandler(handles.tabHandles,1);                                          % Init to overview tab (tab #1)

%
% INITIALIZE VARIABLES
%
set(handles.menuSerialPort,'String',findPorts());                          % Find connected ports
updateControlModels(handles);                                              % Find control models available
handles.HVAC_RX_LENGTH = 24;                                               % Size of return array from HVAC mbed
handles.HVAC_TX_LENGTH = 11;
handles.HVAC_MBED_IDENTIFIER = 39;                                         % Identifier number of HVAC mbed
handles.valveAngles = [90 90 90 90 0 0];                                   % Init angles zone1, zone2, zone3, zone4, exhaust, inlet
handles.blowerStates = [0 0 0];                                            % Set blower 1 speed 0, blower 2 and 3 off
guidata(hObject, handles);

%
% INITIALIZE GUI CONTROL UNITS
%
set(handles.slider1,'Value',0)                                             % Overview tab sliders
set(handles.slider1,'Min',0)
set(handles.slider1,'Max',90)
set(handles.slider2,'Value',0)
set(handles.slider2,'Min',0)
set(handles.slider2,'Max',90)
set(handles.slider3,'Value',0)
set(handles.slider3,'Min',0)
set(handles.slider3,'Max',90)
set(handles.slider4,'Value',0)
set(handles.slider4,'Min',0)
set(handles.slider4,'Max',90)
set(handles.slider1_zone1,'Value',0)                                       % Individual tab sliders
set(handles.slider1_zone1,'Min',0)
set(handles.slider1_zone1,'Max',90)
set(handles.slider2_zone2,'Value',0)
set(handles.slider2_zone2,'Min',0)
set(handles.slider2_zone2,'Max',90)
set(handles.slider3_zone3,'Value',0)
set(handles.slider3_zone3,'Min',0)
set(handles.slider3_zone3,'Max',90)
set(handles.slider4_zone4,'Value',0)
set(handles.slider4_zone4,'Min',0)
set(handles.slider4_zone4,'Max',90)
set(handles.slider1_HVAC,'Min',60)
set(handles.slider1_HVAC,'Max',100)
set(handles.slider1_HVAC,'Value',70)
set(handles.slider2_HVAC,'Value',0)
set(handles.slider2_HVAC,'Min',0)
set(handles.slider2_HVAC,'Max',90)
set(handles.checkbox1,'Value',0);                                          % Manual Control Check Box, initialize off

set(handles.comm,'BackgroundColor',[0.93 0.93 0.93]);


% Update handles structure
guidata(hObject, handles);

% UIWAIT makes GUI wait for user response (see UIRESUME)
uiwait(handles.figure1);
%
% GUI OUTPUT FUNCTION
%
function varargout = GUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
delete(hObject);
%
% TAB CALLBACK FUNCTIONS
%
function tab1_Callback(hObject, eventdata, handles)
tabHandler(handles.tabHandles,1);
function tab2_Callback(hObject, eventdata, handles)
tabHandler(handles.tabHandles,2);
function tab3_Callback(hObject, eventdata, handles)
tabHandler(handles.tabHandles,3);
function tab4_Callback(hObject, eventdata, handles)
tabHandler(handles.tabHandles,4);
function tab5_Callback(hObject, eventdata, handles)
tabHandler(handles.tabHandles,5);
function tab6_Callback(hObject, eventdata, handles)
tabHandler(handles.tabHandles,6);
function tab7_Callback(hObject, eventdata, handles)
tabHandler(handles.tabHandles,7);
updateControlModels(handles);
%
% UPDATE SERIAL PORTS
%
string = findPorts();
string = { string{:} ; 'Specify your own' ; 'IP Communication'};
set(handles.menuSerialPort,'String',string);
set(handles.buttonRefresh,'Value',0);
%
% MENU CALLBACK FUNCTIONS
%
function menuOverview_Callback(hObject, eventdata, handles)
tabHandler(handles.tabHandles,1);
function menuZone1_Callback(hObject, eventdata, handles)
tabHandler(handles.tabHandles,2);
function menuZone2_Callback(hObject, eventdata, handles)
tabHandler(handles.tabHandles,3);
function menuZone3_Callback(hObject, eventdata, handles)
tabHandler(handles.tabHandles,4);
function menuZone4_Callback(hObject, eventdata, handles)
tabHandler(handles.tabHandles,5);
function menuHVAC_Callback(hObject, eventdata, handles)
tabHandler(handles.tabHandles,6);
function menuControl_Callback(hObject, eventdata, handles)
updateControlModels(handles);
set(handles.menuSerialPort,'String',findPorts());
tabHandler(handles.tabHandles,7);
%
% CONTROL TAB CALLBACK FUNCTIONS
%
function menuBlowerControl_Callback(hObject, eventdata, handles)
function menuBlowerControl_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function checkbox1_Callback(hObject, eventdata, handles)
function menuSerialPort_Callback(hObject, eventdata, handles)
str = get(handles.menuSerialPort,'String');
val = get(handles.menuSerialPort,'Value');
%
% ENABLE / DISABLE SPECIFY YOUR OWN PORT
%
if strcmp(str{val},'Specify your own')
    set(handles.textSerial,'Enable','on');
    set(handles.staticSerial,'Enable','on');
    set(handles.staticSerial,'String','Specify Port');
    set(handles.textSerial,'String','Enter Port Name Here');
elseif strcmp(str{val},'IP Communication')
    set(handles.textSerial,'Enable','on');
    set(handles.staticSerial,'Enable','on');
    set(handles.staticSerial,'String','IP Address');
    set(handles.textSerial,'String','158.130.63.155');
else
    set(handles.textSerial,'Enable','off');
    set(handles.staticSerial,'Enable','off'); 
end
function menuSerialPort_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function buttonRefresh_Callback(hObject, eventdata, handles)
string = findPorts();
string = { string{:} ; 'Specify your own' ; 'IP Communication'};
set(handles.menuSerialPort,'String',string);
set(handles.buttonRefresh,'Value',0);
%
% OVERVIEW TAB CALLBACK FUNCTIONS
%
function slider1_Callback(hObject, eventdata, handles)
function slider1_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
function slider2_Callback(hObject, eventdata, handles)
function slider2_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
function slider3_Callback(hObject, eventdata, handles)
function slider3_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
function slider4_Callback(hObject, eventdata, handles)
function slider4_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
%
% ZONE1 TAB CALLBACK FUNCTIONS
%
function slider1_zone1_Callback(hObject, eventdata, handles)
function slider1_zone1_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
%
% ZONE2 TAB CALLBACK FUNCTIONS
%
function slider2_zone2_Callback(hObject, eventdata, handles)
function slider2_zone2_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
%
% ZONE3 TAB CALLBACK FUNCTIONS
%
function slider3_zone3_Callback(hObject, eventdata, handles)
function slider3_zone3_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
%
% ZONE4 TAB CALLBACK FUNCTIONS
%
function slider4_zone4_Callback(hObject, eventdata, handles)
function slider4_zone4_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
%
% BUTTON CALLBACK FUNCTIONS
%
function buttonSave_Callback(hObject, eventdata, handles)
saveGUI( handles );
function buttonExit_Callback(hObject, eventdata, handles)
handles.stopTransmit = 1;
guidata(hObject,handles);
uiresume(handles.figure1);
function buttonStop_Callback(hObject, eventdata, handles)
set(handles.rb_master_flow,'Value',0);
set(handles.rb_master_speed,'Value',0);
set(handles.rb_master_temp,'Value',0);
set(handles.rb_master_servo,'Value',0);
handles.stopTransmit = 1;
guidata(hObject,handles);

function buttonStart_Callback(hObject, eventdata, handles)

%
% DISABLE SOME SELECTION OPTIONS
%
set(handles.buttonStepBack,'Enable','off');                                % Disable time step buttons
set(handles.buttonStepForward,'Enable','off');                             % ^
set(handles.cb_save,'Enable','off');                                       % Disable 'Save Video' check box
set(handles.text2,'Enable','off');                                         % Disable port selection
set(handles.menuSerialPort,'Enable','off');                                % ^
set(handles.textSerial,'Enable','off');                                    % ^
set(handles.staticSerial,'Enable','off');                                  % ^
%
% INITIALIZE CONTROL
%
initControl(handles);                                                      % Initialize control models
controlPeriod = str2num( get(handles.textControlPeriod,'String') );        % Control calculation Period in seconds
finalZoneState = [];                                                       % Final state of simulink model for zone control
finalHVACState = [];                                                       % Final state of simulink model for HVAC control

%
% SELECT CONTROL MODELS
%
str = get(handles.menuZoneControl,'String');
val = get(handles.menuZoneControl,'Value');
zoneMDL = str{val};
clear str val
str = get(handles.menuBlowerControl,'String');
val = get(handles.menuBlowerControl,'Value');
blowerMDL = str{val};
clear str val

%
% INITIALIZE COMMUNICATION
%
delete(instrfind);                                                         % Clear all previous ports (solves issues when improperly closed)
string = findPorts();                                                      % Must update ports manually, only occurs on tab switching
string = { string{:} ; 'Specify your own' ; 'IP Communication'};           % ^
set(handles.menuSerialPort,'String',string);                               % ^
str=get(handles.menuSerialPort,'String');                                  % Find the available ports listed in pop up menu
val=get(handles.menuSerialPort,'Value');                                   % ^
if strcmp(str{val},'No ports found')                                       % If no ports were found, and none specified ...
    warndlg('You have not specified an appropriate port','!! Warning !!')  % ... tell the user and do not contine
    return                                                                 % ^
elseif strcmp(str{val},'Specify your own')                                 % Determine whether automatically found or individually specified
    str = get(handles.textSerial,'String');                                % ^
    handles.USB_PATH = str{1};                                             % ^
    handles.handle = serial(handles.USB_PATH,'Timeout',0.2);               % Set serial port
elseif strcmp(str{val},'IP Communication')                                 % If you want to communicate over IP
    host = get(handles.textSerial,'String');
    port_send = 25000;
    port_receive = 27000;
    handles.handle = udp(host,'localport',port_receive,'remoteport',port_send,'DatagramTerminateMode','off','inputbuffersize',handles.HVAC_RX_LENGTH,'outputbuffersize',handles.HVAC_TX_LENGTH);                                                                       
else                                                                       % ^
    handles.USB_PATH = str{val};                                           % ^
    handles.handle = serial(handles.USB_PATH,'Timeout',0.2);               % Set serial port
end                                                                        % ^
guidata(hObject,handles);                   
fclose(handles.handle);                                                    % 
try                                                                        % Try to open the serial port ...
    fopen(handles.handle);                                                 % ...Open serial port
catch err                                                                  % If an error arose (port could not be opened)
    warndlg('The specified port is incorrect','!! Warning !!')             % ... tell the user and do not contine
    return                                                                 % ^
end                                                                        % ^
pause(2);                                                                  % Pause seems necessary (1 smallest with success)

%
% INITIALIZE VIDEO
%
if get(handles.cb_save,'Value')                                            % If you want to save the video
    out = inputdlg('Save Video As:');                                      % ... Ask user for save path
    vidObj = VideoWriter(strcat(out{1},'.avi'),'Motion JPEG AVI');         % ... Create the object
    vidObj.FrameRate = 3;                                                  % ... Specify the frame rate at 3 fps
    open(vidObj);                                                          % ... Open the video object
end                                                                        % ^

%
% INITIALIZE VARIABLES
%
transmitFlag = 1;                                                          % General variables                                                        
handles.stopTransmit = 0;
handles.dbValve = 90;
fail = 0;
output.time = [];                                                          % Clear and initialize all data
output.temp.z1 = [];
output.temp.z2 = [];
output.temp.z3 = [];
output.temp.z4 = [];
output.temp.HVAC = [];
output.temp.Amb = [];
output.filterTemp.z1 = [];
output.filterTemp.z2 = [];
output.filterTemp.z3 = [];
output.filterTemp.z4 = [];
output.filterTemp.HVAC = [];
output.filterTemp.Amb = [];
output.flow.z1 = [];
output.flow.z2 = [];
output.flow.z3 = [];
output.flow.z4 = [];
output.flow.HVAC = [];
output.speed.z1 = [];
output.speed.z2 = [];
output.speed.z3 = [];
output.speed.z4 = [];
output.speed.HVAC = [];
output.valve.z1 = [];
output.valve.z2 = [];
output.valve.z3 = [];
output.valve.z4 = [];
output.valve.exhaust = [];
output.valve.inlet = [];
output.blower.supply = [];
output.blower.return = [];
output.blower.cooler = [];
output.temp.units = 'C';
output.current.blower = [];
output.current.heater = [];
output.power.blower = [];
output.power.heater = [];
guidata(hObject,handles);

%
% SEND INITIAL PACKET
%
fwrite(handles.handle, [handles.HVAC_MBED_IDENTIFIER , handles.valveAngles , handles.blowerStates , handles.dbValve]); % Write first packet to HVAC mbed ...
try                                                                        % Try to read from the serial port
    buffer = fread(handles.handle,handles.HVAC_RX_LENGTH);                 % ... and read the response
    if numel(buffer) ~= handles.HVAC_RX_LENGTH                             %
        error('incorrect rx length')
        set(handles.comm,'BackgroundColor',[1 0 0]);
    end
catch err
    warndlg('The Port may not be correct, the specified amount of data was not returned.','!! Warning !!')
    return
end
set(handles.comm,'BackgroundColor',[0 1 0]);
    

tStart = tic;                                                              % Start the data timer
tControl = tic;                                                            % Start the control timer
while( transmitFlag ) 
    %
    % INTERPRET DATA
    %
    output.time = [ output.time ; toc(tStart) ];                                        % Store time data
    output.temp.z1 = [ output.temp.z1 ; 330*(256*buffer(2)+buffer(3))/65536-50 ];       % Store temperature (converted from raw 16-bit ADC)
    output.temp.z2 = [ output.temp.z2 ; 330*(256*buffer(4)+buffer(5))/65536-50 ];       % ^
    output.temp.z3 = [ output.temp.z3 ; 330*(256*buffer(9)+buffer(10))/65536-50 ];      % ^
    output.temp.z4 = [ output.temp.z4 ; 330*(256*buffer(11)+buffer(12))/65536-50 ];     % ^
    output.temp.HVAC = [ output.temp.HVAC ; 330*(256*buffer(16)+buffer(17))/65536-50 ]; % ^
    output.temp.Amb = [ output.temp.Amb ; 330*(256*buffer(18)+buffer(19))/65536-50 ];  % ^ 
    output.speed.z1 = [ output.speed.z1 ; 0.06*buffer(6) ];                             % Store speed (converted from Hz of flow meter) 
    output.speed.z2 = [ output.speed.z2 ; 0.06*buffer(7) ];                             % ^
    output.speed.z3 = [ output.speed.z3 ; 0.06*buffer(13) ];                            % ^
    output.speed.z4 = [ output.speed.z4 ; 0.06*buffer(14) ];                            % ^
    output.speed.HVAC = [ output.speed.HVAC ; 0.06*buffer(20) ];                        % ^
    output.flow.z1 = 197*0.0055*output.speed.z1;                                        % Store flow (converted from speed)
    output.flow.z2 = 197*0.0055*output.speed.z2;                                        % ^
    output.flow.z3 = 197*0.0055*output.speed.z3;                                        % ^
    output.flow.z4 = 197*0.0055*output.speed.z4;                                        % ^
    output.flow.HVAC = 197*0.0055*output.speed.HVAC;                                    % ^
    output.valve.z1 = [ output.valve.z1 ; handles.valveAngles(1) ];                     % Store valve angle
    output.valve.z2 = [ output.valve.z2 ; handles.valveAngles(2) ];                     % ^
    output.valve.z3 = [ output.valve.z3 ; handles.valveAngles(3) ];                     % ^
    output.valve.z4 = [ output.valve.z4 ; handles.valveAngles(4) ];                     % ^
    output.valve.exhaust = [ output.valve.exhaust ; handles.valveAngles(5) ];           % ^
    output.valve.inlet = [ output.valve.inlet ; handles.valveAngles(6) ];               % ^
    output.filterTemp.z1 = filterTemp(output.temp.z1,output.filterTemp.z1);             % Filter the temperature data
    output.filterTemp.z2 = filterTemp(output.temp.z2,output.filterTemp.z2);             % ^
    output.filterTemp.z3 = filterTemp(output.temp.z3,output.filterTemp.z3);             % ^
    output.filterTemp.z4 = filterTemp(output.temp.z4,output.filterTemp.z4);             % ^
    output.filterTemp.HVAC = filterTemp(output.temp.HVAC,output.filterTemp.HVAC);       % ^
    output.filterTemp.Amb = filterTemp(output.temp.Amb,output.filterTemp.Amb);          % ^
    output.blower.supply = [ output.blower.supply ; handles.blowerStates(1) ];          % Store the blower supply speed
    output.blower.return = [ output.blower.return ; handles.blowerStates(2) ];          % ^
    output.blower.cooler = [ output.blower.cooler ; handles.blowerStates(3) ];          % ^
    output.current.blower = [ output.current.blower ; 0.00004425*(256*buffer(20)+buffer(21)) - 1.38557 ];      % Store the current and power
    output.current.heater = [ output.current.heater ; 0 ];      % ^
    %output.current.heater = [ output.current.heater ; 256*buffer(22)+buffer(23) ];      % ^
    output.power.blower = (12.681*output.current.blower+0.3942).*output.current.blower;  % Convert current to power
    output.power.heater = 120*output.current.heater;                                    % ^
    
    len = numel(output.time);
    tempZONE = [output.filterTemp.z1(len) , output.filterTemp.z2(len) , output.filterTemp.z3(len) , output.filterTemp.z4(len) , output.valve.z1(len) , output.valve.z2(len) , output.valve.z3(len) , output.valve.z4(len)];
    tempHVAC = [output.valve.z1(len) , output.valve.z2(len) , output.valve.z3(len) , output.valve.z4(len) , output.flow.z1(len) , output.flow.z2(len) , output.flow.z3(len) , output.flow.z4(len)];
    
    temp = output;
    %
    % CONVERT TEMP UNIT                                                    Store the data, convert it to F, plot the data, return the data to its original state
    % 
    %
    if get(handles.rb_temp_units_f,'Value')                                % Convert to F
        tempUnits = 'F';
        output.temp.z1 = ( 1.8 * output.temp.z1 ) + 32;
        output.temp.z2 = ( 1.8 * output.temp.z2 ) + 32;
        output.temp.z3 = ( 1.8 * output.temp.z3 ) + 32;
        output.temp.z4 = ( 1.8 * output.temp.z4 ) + 32; 
        output.temp.HVAC = ( 1.8 * output.temp.HVAC ) + 32; 
        output.filterTemp.z1 = ( 1.8 * output.filterTemp.z1 ) + 32;
        output.filterTemp.z2 = ( 1.8 * output.filterTemp.z2 ) + 32;
        output.filterTemp.z3 = ( 1.8 * output.filterTemp.z3 ) + 32;
        output.filterTemp.z4 = ( 1.8 * output.filterTemp.z4 ) + 32; 
        output.filterTemp.HVAC = ( 1.8 * output.filterTemp.HVAC ) + 32; 
    else
        tempUnits = 'C';
    end
    
    %
    % PRINT DATA
    %
    if get(handles.tab1,'Value')                                           % Print based on whatever tab is active
        printOverview(handles,output,tempUnits);      
    elseif get(handles.tab2,'Value')
        printZone1(handles,output,tempUnits);
    elseif get(handles.tab3,'Value')
        printZone2(handles,output,tempUnits);
    elseif get(handles.tab4,'Value');
        printZone3(handles,output,tempUnits);
    elseif get(handles.tab5,'Value')
        printZone4(handles,output,tempUnits);
    elseif get(handles.tab6,'Value')
        printHVAC(handles,output,tempUnits);
    end
    output = temp;
    
    % 
    % CONTROL
    %
    handles.blowerStates = blowerHandler( handles );                       % Update sliders
    handles.valveAngles = valveHandler(handles,handles.valveAngles);       % ^
    guidata(hObject,handles);                                              % ^
    tempAngles = handles.valveAngles(:,5:6);
    tempBlower = handles.blowerStates(:,2:3);
    if ~get(handles.checkbox1,'Value')                                     % If manual control not allowed (i.e. model control enabled)
        if toc(tControl) > controlPeriod
            % Only calculates zone valves
            [handles.valveAngles finalZoneState] = calcZoneControl( zoneMDL , tempZONE , toc(tStart) , controlPeriod , finalZoneState );
            handles.valveAngles = [ handles.valveAngles , tempAngles ];
            [blowerOutputs finalHVACState] = calcHVACControl( blowerMDL , tempHVAC , toc(tStart) , controlPeriod , finalHVACState );
            handles.blowerStates = [ blowerOutputs , tempBlower ];
            guidata(hObject,handles);
            tControl = tic;
        end
    end
    
    %
    % WRITE AND RECIEVE DATA
    %
    %write = [handles.HVAC_MBED_IDENTIFIER , handles.valveAngles , handles.blowerStates, handles.dbValve];
    fwrite(handles.handle,[handles.HVAC_MBED_IDENTIFIER , handles.valveAngles , handles.blowerStates, handles.dbValve]);
    %pause(0.2);
    out = fread(handles.handle,handles.HVAC_RX_LENGTH);
    if numel(out) == handles.HVAC_RX_LENGTH                                % Check that the correct number of packets were received
        buffer = out;                                                      % ... if so store them in the buffer
        fail = 0;
        set(handles.comm,'BackgroundColor',[0 1 0]);
    else
        fail = fail + 1;                                                   % ... else increment the fail count
        set(handles.comm,'BackgroundColor',[1 0 0]);
    end
    if fail >= 5                                                           % If you have failed more than 5 times in a row, quit the loop
        fclose(handles.handle);                                            % ^
        delete(instrfind);                                                 % ^
        clear handles.handle                                               % ^
        warndlg('Failed to receive correct number of packets 5 successive times','!! Warning !!')
        return                                                             % ^
    end                                                                    % ^
    
    %
    % SAVE VIDEO FILE, IF DESIRED
    %
    if get(handles.cb_save,'Value')
        frame = getframe(handles.figure1);
        writeVideo(vidObj,frame.cdata);
    end
    
    %
    % CHECK FOR TERMINATION
    %
    drawnow;                                                               % this allows to be interrupted by exit button
    handles=guidata(hObject);
    if handles.stopTransmit                                                % If you press stop ...
        transmitFlag = 0;                                                  % ... stop the transmit
        fwrite(handles.handle,[handles.HVAC_MBED_IDENTIFIER handles.valveAngles 0 0 0 90]); % ... and write one last packet to mbed to shut off blowers
        fread(handles.handle,handles.HVAC_RX_LENGTH);
    end
    
    
handles.output = output;
guidata(hObject,handles);
end

%
% CLEANUP
%
fclose(handles.handle);
delete(instrfind);
clear handles.handle
handles.output = output;
guidata(hObject,handles);
set(handles.cb_save,'Enable','on');
if get(handles.cb_save,'Value')
    close(vidObj);
end
set(handles.buttonStepBack,'Enable','on');
set(handles.buttonStepForward,'Enable','on');
set(handles.text2,'Enable','off');                                         % Enable port selection
set(handles.menuSerialPort,'Enable','off');                                % ^
set(handles.textSerial,'Enable','off');                                    % ^
set(handles.staticSerial,'Enable','off');                                  % ^
printOverview(handles,output,tempUnits);                                   % Print all data 
printZone1(handles,output,tempUnits);
printZone2(handles,output,tempUnits);
printZone3(handles,output,tempUnits);
printZone4(handles,output,tempUnits);
printHVAC(handles,output,tempUnits);

function menuZone1Control_Callback(hObject, eventdata, handles)
function menuControl_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function text_1_low_sp_Callback(hObject, eventdata, handles)
function text_1_low_sp_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function text_1_high_sp_Callback(hObject, eventdata, handles)
function text_1_high_sp_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function panelTempUnits_SelectionChangeFcn(hObject, eventdata, handles)
if get(handles.rb_temp_units_c,'Value')
    %
    % CHANGE ZONE 1
    %
    set(handles.static_1_low_sp,'String','Low Set Point [C]');
    set(handles.static_1_high_sp,'String','High Set Point [C]');
    set(handles.text_1_low_sp,'String', num2str( ( str2num( get(handles.text_1_low_sp,'String') ) - 32 ) / 1.8 , '%0.2f' ) );
    set(handles.text_1_high_sp,'String', num2str( ( str2num( get(handles.text_1_high_sp,'String') ) - 32 ) / 1.8 , '%0.2f') ); 
    %
    % CHANGE ZONE 2
    % 
    set(handles.static_2_low_sp,'String','Low Set Point [C]');
    set(handles.static_2_high_sp,'String','High Set Point [C]');
    set(handles.text_2_low_sp,'String', num2str( ( str2num( get(handles.text_2_low_sp,'String') ) - 32 ) / 1.8 , '%0.2f' ) );
    set(handles.text_2_high_sp,'String', num2str( ( str2num( get(handles.text_2_high_sp,'String') ) - 32 ) / 1.8 , '%0.2f' ) ); 
    %
    % CHANGE ZONE 3
    %
    set(handles.static_3_low_sp,'String','Low Set Point [C]');
    set(handles.static_3_high_sp,'String','High Set Point [C]');
    set(handles.text_3_low_sp,'String', num2str( ( str2num( get(handles.text_3_low_sp,'String') ) - 32 ) / 1.8 , '%0.2f' ) );
    set(handles.text_3_high_sp,'String', num2str( ( str2num( get(handles.text_3_high_sp,'String') ) - 32 ) / 1.8 , '%0.2f') ); 
    %
    % CHANGE ZONE 4
    % 
    set(handles.static_4_low_sp,'String','Low Set Point [C]');
    set(handles.static_4_high_sp,'String','High Set Point [C]');
    set(handles.text_4_low_sp,'String', num2str( ( str2num( get(handles.text_4_low_sp,'String') ) - 32 ) / 1.8 , '%0.2f' ) );
    set(handles.text_4_high_sp,'String', num2str( ( str2num( get(handles.text_4_high_sp,'String') ) - 32 ) / 1.8 , '%0.2f' ) ); 
else
    %
    % CHANGE ZONE 1
    %
    set(handles.static_1_low_sp,'String','Low Set Point [F]');
    set(handles.static_1_high_sp,'String','High Set Point [F]');
    set(handles.text_1_low_sp,'String', num2str( 1.8*str2num( get(handles.text_1_low_sp,'String') ) + 32 , '%0.2f' ) );
    set(handles.text_1_high_sp,'String', num2str( 1.8*str2num( get(handles.text_1_high_sp,'String') ) + 32 , '%0.2f' ) ); 
    %
    % CHANGE ZONE 2
    % 
    set(handles.static_2_low_sp,'String','Low Set Point [F]');
    set(handles.static_2_high_sp,'String','High Set Point [F]');
    set(handles.text_2_low_sp,'String', num2str( 1.8*str2num( get(handles.text_2_low_sp,'String') ) + 32 , '%0.2f' ) );
    set(handles.text_2_high_sp,'String', num2str( 1.8*str2num( get(handles.text_2_high_sp,'String') ) + 32 , '%0.2f' ) ); 
    %
    % CHANGE ZONE 3
    %
    set(handles.static_3_low_sp,'String','Low Set Point [F]');
    set(handles.static_3_high_sp,'String','High Set Point [F]');
    set(handles.text_3_low_sp,'String', num2str( 1.8*str2num( get(handles.text_3_low_sp,'String') ) + 32 , '%0.2f' ) );
    set(handles.text_3_high_sp,'String', num2str( 1.8*str2num( get(handles.text_3_high_sp,'String') ) + 32 , '%0.2f' ) ); 
    %
    % CHANGE ZONE 4
    % 
    set(handles.static_4_low_sp,'String','Low Set Point [F]');
    set(handles.static_4_high_sp,'String','High Set Point [F]');
    set(handles.text_4_low_sp,'String', num2str( 1.8*str2num( get(handles.text_4_low_sp,'String') ) + 32 , '%0.2f' ) );
    set(handles.text_4_high_sp,'String', num2str( 1.8*str2num( get(handles.text_4_high_sp,'String') ) + 32 , '%0.2f' ) );
end

function menuZone2Control_Callback(hObject, eventdata, handles)
function menuZone2Control_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function text_2_low_sp_Callback(hObject, eventdata, handles)
function text_2_low_sp_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function text_2_high_sp_Callback(hObject, eventdata, handles)
function text_2_high_sp_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function menuZone4Control_Callback(hObject, eventdata, handles)
function menuZone4Control_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function text_4_low_sp_Callback(hObject, eventdata, handles)
function text_4_low_sp_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function text_4_high_sp_Callback(hObject, eventdata, handles)
function text_4_high_sp_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function menuZone3Control_Callback(hObject, eventdata, handles)
function menuZone3Control_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function text_3_low_sp_Callback(hObject, eventdata, handles)
function text_3_low_sp_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function text_3_high_sp_Callback(hObject, eventdata, handles)
function text_3_high_sp_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function slider1_HVAC_Callback(hObject, eventdata, handles)
function slider1_HVAC_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
function slider13_Callback(hObject, eventdata, handles)
function slider13_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
function slider2_HVAC_Callback(hObject, eventdata, handles)
function slider2_HVAC_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

function panelRecycleValves_SelectionChangeFcn(hObject, eventdata, handles)


if get(handles.rb_HVAC_exhaust,'Value')
    handles.valveAngles(6) = get(handles.slider2_HVAC,'Value');
    set(handles.slider2_HVAC,'Value',handles.valveAngles(5));
elseif get(handles.rb_HVAC_inlet,'Value')
    handles.valveAngles(5) = get(handles.slider2_HVAC,'Value');
    set(handles.slider2_HVAC,'Value',handles.valveAngles(6));
end
     
function cb_save_Callback(hObject, eventdata, handles)
function textSerial_Callback(hObject, eventdata, handles)
function textSerial_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function buttonStepBack_Callback(hObject, eventdata, handles)

time = xlim(handles.axes1);
tStart = time(1);
tEnd = time(2);
tStart = tStart - 5;
tEnd = tEnd - 5;
if tStart < 0
    tStart = 0;
end
if tEnd < 30
    tEnd = 30;
end

xlim(handles.axes1,[tStart,tEnd]);
xlim(handles.axes2,[tStart,tEnd]);
xlim(handles.axes3,[tStart,tEnd]);
xlim(handles.axes4,[tStart,tEnd]);
xlim(handles.axes1_zone1,[tStart,tEnd]);
xlim(handles.axes2_zone1,[tStart,tEnd]);
xlim(handles.axes3_zone1,[tStart,tEnd]);
xlim(handles.axes4_zone1,[tStart,tEnd]);
xlim(handles.axes1_zone2,[tStart,tEnd]);
xlim(handles.axes2_zone2,[tStart,tEnd]);
xlim(handles.axes3_zone2,[tStart,tEnd]);
xlim(handles.axes4_zone2,[tStart,tEnd]);
xlim(handles.axes1_zone3,[tStart,tEnd]);
xlim(handles.axes2_zone3,[tStart,tEnd]);
xlim(handles.axes3_zone3,[tStart,tEnd]);
xlim(handles.axes4_zone3,[tStart,tEnd]);
xlim(handles.axes1_zone4,[tStart,tEnd]);
xlim(handles.axes2_zone4,[tStart,tEnd]);
xlim(handles.axes3_zone4,[tStart,tEnd]);
xlim(handles.axes4_zone4,[tStart,tEnd]);
xlim(handles.axes1_HVAC,[tStart,tEnd]);
xlim(handles.axes2_HVAC,[tStart,tEnd]);

function buttonStepForward_Callback(hObject, eventdata, handles)

time = xlim(handles.axes1);
tStart = time(1);
tEnd = time(2);
tStart = tStart + 5;
tEnd = tEnd + 5;
if tEnd > handles.output.time( numel(handles.output.time) )
    tEnd = handles.output.time( numel(handles.output.time) );
    tStart = tEnd - 200;
    if tStart < 0
        tStart = 0;
    end
end
if tEnd < 200
    tStart = 0;
end

xlim(handles.axes1,[tStart,tEnd]);
xlim(handles.axes2,[tStart,tEnd]);
xlim(handles.axes3,[tStart,tEnd]);
xlim(handles.axes4,[tStart,tEnd]);
xlim(handles.axes1_zone1,[tStart,tEnd]);
xlim(handles.axes2_zone1,[tStart,tEnd]);
xlim(handles.axes3_zone1,[tStart,tEnd]);
xlim(handles.axes4_zone1,[tStart,tEnd]);
xlim(handles.axes1_zone2,[tStart,tEnd]);
xlim(handles.axes2_zone2,[tStart,tEnd]);
xlim(handles.axes3_zone2,[tStart,tEnd]);
xlim(handles.axes4_zone2,[tStart,tEnd]);
xlim(handles.axes1_zone3,[tStart,tEnd]);
xlim(handles.axes2_zone3,[tStart,tEnd]);
xlim(handles.axes3_zone3,[tStart,tEnd]);
xlim(handles.axes4_zone3,[tStart,tEnd]);
xlim(handles.axes1_zone4,[tStart,tEnd]);
xlim(handles.axes2_zone4,[tStart,tEnd]);
xlim(handles.axes3_zone4,[tStart,tEnd]);
xlim(handles.axes4_zone4,[tStart,tEnd]);
xlim(handles.axes1_HVAC,[tStart,tEnd]);
xlim(handles.axes2_HVAC,[tStart,tEnd]);

function edit14_Callback(hObject, eventdata, handles)
function edit14_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function edit15_Callback(hObject, eventdata, handles)
function edit15_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function edit12_Callback(hObject, eventdata, handles)
function edit12_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function edit13_Callback(hObject, eventdata, handles)
function edit13_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function edit10_Callback(hObject, eventdata, handles)
function edit10_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function edit11_Callback(hObject, eventdata, handles)
function edit11_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function edit16_Callback(hObject, eventdata, handles)
function edit16_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function edit17_Callback(hObject, eventdata, handles)
function edit17_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function menuZoneControl_Callback(hObject, eventdata, handles)
function menuZoneControl_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function rb_heat_Callback(hObject, eventdata, handles)
function rb_cool_Callback(hObject, eventdata, handles)
function uipanel40_SelectionChangeFcn(hObject, eventdata, handles)
if get(handles.rb_heat,'Value')
    handles.dbValve = 0;
else
    handles.dbValve = 90;
end
initControl(handles);
guidata(hObject,handles);    
function uipanel41_SelectionChangeFcn(hObject, eventdata, handles)

if get(handles.rb_master_flow,'Value')
    set(handles.rb_1_flow,'Value',1);
    set(handles.rb_2_flow,'Value',1);
    set(handles.rb_3_flow,'Value',1);
    set(handles.rb_4_flow,'Value',1);
elseif get(handles.rb_master_speed,'Value')
    set(handles.rb_1_speed,'Value',1);
    set(handles.rb_2_speed,'Value',1);
    set(handles.rb_3_speed,'Value',1);
    set(handles.rb_4_speed,'Value',1);
elseif get(handles.rb_master_temp,'Value')
    set(handles.rb_1_temp,'Value',1);
    set(handles.rb_2_temp,'Value',1);
    set(handles.rb_3_temp,'Value',1);
    set(handles.rb_4_temp,'Value',1);
else
    set(handles.rb_1_servo,'Value',1);
    set(handles.rb_2_servo,'Value',1);
    set(handles.rb_3_servo,'Value',1);
    set(handles.rb_4_servo,'Value',1);
end
function buttonPannel1_SelectionChangeFcn(hObject, eventdata, handles)
set(handles.rb_master_flow,'Value',0);
set(handles.rb_master_speed,'Value',0);
set(handles.rb_master_temp,'Value',0);
set(handles.rb_master_servo,'Value',0);
function buttonPannel2_SelectionChangeFcn(hObject, eventdata, handles)
set(handles.rb_master_flow,'Value',0);
set(handles.rb_master_speed,'Value',0);
set(handles.rb_master_temp,'Value',0);
set(handles.rb_master_servo,'Value',0);
function bottonPannel3_SelectionChangeFcn(hObject, eventdata, handles)
set(handles.rb_master_flow,'Value',0);
set(handles.rb_master_speed,'Value',0);
set(handles.rb_master_temp,'Value',0);
set(handles.rb_master_servo,'Value',0);
function buttonPannel4_SelectionChangeFcn(hObject, eventdata, handles)
set(handles.rb_master_flow,'Value',0);
set(handles.rb_master_speed,'Value',0);
set(handles.rb_master_temp,'Value',0);
set(handles.rb_master_servo,'Value',0);

function textControlPeriod_Callback(hObject, eventdata, handles)
function textControlPeriod_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
