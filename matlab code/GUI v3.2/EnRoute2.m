% EnRoute 2.0 Configuration File

warning off all
clc

addpath(genpath('DATA CONTROL/'),genpath('GUI SUPPORT/'),genpath('SAVE GUI/'),genpath('SERIAL PORT/'),genpath('CONTROL MODELS'));        % Add folders to path

open_system('ON_OFF');
open_system('ON_OFF_LAZY');
open_system('K_LAZY');
open_system('K_VALVE');

GUI

% save_system('ON_OFF');
% save_system('ON_OFF_LAZY');
% save_system('K_VALVE');
close_system('ON_OFF',0);
close_system('ON_OFF_LAZY',0);
close_system('K_LAZY',0);
close_system('K_VALVE',0);

clear