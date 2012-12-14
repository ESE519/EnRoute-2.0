function ports = findPorts( )
% Author Dan Wheeler
% November 15, 2012
% FINDPORTS finds all the serial ports connected to a computer 
%
%   OUTPUTS:  
%       ports   =   Cell Array of available ports
%

ports{1} = 'No ports found';

if ismac
    out = dir('/dev/tty.usbmodem*');
    for i = 1:size(out,1)
        ports{i} = strcat('/dev/',out(i).name);
    end
elseif isunix 
    out = dir('/dev/ttyACM*');
    for i = 1:size(out,1)
        ports{i} = strcat('/dev/',out(i).name);
    end   
elseif win
    
end


end

