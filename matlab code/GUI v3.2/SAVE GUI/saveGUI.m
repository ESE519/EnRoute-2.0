function varargout = saveGUI(varargin)
% SAVEGUI MATLAB code for saveGUI.fig
%      SAVEGUI, by itself, creates a new SAVEGUI or raises the existing
%      singleton*.
%
%      H = SAVEGUI returns the handle to a new SAVEGUI or the handle to
%      the existing singleton*.
%
%      SAVEGUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SAVEGUI.M with the given input arguments.
%
%      SAVEGUI('Property','Value',...) creates a new SAVEGUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before saveGUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to saveGUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help saveGUI

% Last Modified by GUIDE v2.5 21-Nov-2012 01:10:12

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @saveGUI_OpeningFcn, ...
                   'gui_OutputFcn',  @saveGUI_OutputFcn, ...
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
% End initialization code - DO NOT EDIT


% --- Executes just before saveGUI is made visible.
function saveGUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to saveGUI (see VARARGIN)

% Choose default command line output for saveGUI
handles.output = hObject;

%
% PARSE INPUT VARIABLES
%
handles.h = varargin{1};

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes saveGUI wait for user response (see UIRESUME)
uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = saveGUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

delete(hObject);



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in buttonSave.
function buttonSave_Callback(hObject, eventdata, handles)
% hObject    handle to buttonSave (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

saveString = get(handles.edit1,'String');

if get(handles.cb_data,'Value')
    stringOut = strcat( saveString , '_data' , '.mat');
    data = handles.h.output;
    save(stringOut,'data');
end
if get(handles.cb_overview,'Value')
    stringOut = strcat( saveString , '_overview' , '.jpg');
    tabHandler(handles.h.tabHandles,1);
    frame = getframe(handles.h.figure1);
    imwrite(frame.cdata,stringOut);
end
if get(handles.cb_zone1,'Value')
    stringOut = strcat( saveString , '_zone1' , '.jpg');
    tabHandler(handles.h.tabHandles,2);
    frame = getframe(handles.h.figure1);
    imwrite(frame.cdata,stringOut);
end
if get(handles.cb_zone2,'Value')
    stringOut = strcat( saveString , '_zone2' , '.jpg');
    tabHandler(handles.h.tabHandles,3);
    frame = getframe(handles.h.figure1);
    imwrite(frame.cdata,stringOut);    
end
if get(handles.cb_zone3,'Value')
    stringOut = strcat( saveString , '_zone3' , '.jpg');
    tabHandler(handles.h.tabHandles,4);
    frame = getframe(handles.h.figure1);
    imwrite(frame.cdata,stringOut);    
end
if get(handles.cb_zone4,'Value')
    stringOut = strcat( saveString , '_zone4' , '.jpg');
    tabHandler(handles.h.tabHandles,5);
    frame = getframe(handles.h.figure1);
    imwrite(frame.cdata,stringOut);    
end
if get(handles.cb_HVAC,'Value')
    stringOut = strcat( saveString , '_HVAC' , '.jpg');
    tabHandler(handles.h.tabHandles,6);
    frame = getframe(handles.h.figure1);
    imwrite(frame.cdata,stringOut);    
end
if get(handles.cb_control,'Value')
    stringOut = strcat( saveString , '_control' , '.jpg');
    tabHandler(handles.h.tabHandles,7);
    frame = getframe(handles.h.figure1);
    imwrite(frame.cdata,stringOut);
end

uiresume(handles.figure1);


% --- Executes on button press in buttonCancel.
function buttonCancel_Callback(hObject, eventdata, handles)
% hObject    handle to buttonCancel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

uiresume(handles.figure1);


% --- Executes on button press in cb_data.
function cb_data_Callback(hObject, eventdata, handles)
% hObject    handle to cb_data (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of cb_data


% --- Executes on button press in cb_overview.
function cb_overview_Callback(hObject, eventdata, handles)
% hObject    handle to cb_overview (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of cb_overview


% --- Executes on button press in cb_zone1.
function cb_zone1_Callback(hObject, eventdata, handles)
% hObject    handle to cb_zone1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of cb_zone1


% --- Executes on button press in cb_zone2.
function cb_zone2_Callback(hObject, eventdata, handles)
% hObject    handle to cb_zone2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of cb_zone2


% --- Executes on button press in cb_zone3.
function cb_zone3_Callback(hObject, eventdata, handles)
% hObject    handle to cb_zone3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of cb_zone3


% --- Executes on button press in cb_zone4.
function cb_zone4_Callback(hObject, eventdata, handles)
% hObject    handle to cb_zone4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of cb_zone4


% --- Executes on button press in cb_HVAC.
function cb_HVAC_Callback(hObject, eventdata, handles)
% hObject    handle to cb_HVAC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of cb_HVAC


% --- Executes on button press in cb_control.
function cb_control_Callback(hObject, eventdata, handles)
% hObject    handle to cb_control (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of cb_control
