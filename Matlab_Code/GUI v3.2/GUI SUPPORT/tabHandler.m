function tabHandler( handles , numOn)
% Author Dan Wheeler
% November 12, 2012
% ESE 519 EnRoute 2.0 
% TABHANDLER handles "tab" switching for GUI 
%
%   INPUTS:  
%       handles     =   1(x)2n vector where first n elements are for 
%                       pannel handles, second n elements are for 
%                       button handles
%       numOn       =   The "tab" number to turn on
%

%
% ERROR HANDLING
%
if size(handles,1) ~= 1
    error('Handle array must be 1 x n');
end
if numOn > 0.5*size(handles,2)
    error('Trying to turn on a tab that does not exist')
end
if numOn < 1
    error('numOn must be positive')
end

%
% TAB SWITCHING
%
num = 0.5*size(handles,2);

for i=1:num
    if i == numOn
        set(handles(i),'Visible','on');
        set(handles(i+num),'Value',1);
    else
        set(handles(i),'Visible','off');
        set(handles(i+num),'Value',0);  
    end
end


end

