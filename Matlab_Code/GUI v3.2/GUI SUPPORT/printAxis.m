function printAxis( varargin )
% Author Dan Wheeler
% November 10, 2012
% ESE 519 EnRoute 2.0 (general for all purposes)
% PRINTAXIS combines formatting for printing to axes, specifically for GUI with multiple graphs 
%
%   INPUTS:  [axisLabel, xData, yData, xLabel, yLabel, limits, color, clearFlag]
%       axisLabel   =   Handle to desired axis
%       xData       =   x-data to be plotted
%       yData       =   y-data to be plotted
%       xLabel      =   x-label for plot (optional)
%       yLabel      =   y-label for plot (optional)
%                       You must include both labels, or neither
%       limits      =   Limits for plot [xmin xmax ymin ymax] (optional)
%                       You must place limits as 1x4 array
%                       If only 2 elements to array, it is y
%       color       =   Color of printed data (optional)
%                       Color value must match available colors by default in matlab
%       clearFlag   =   If set (1) clears the axis before plotting (optional)
%
%   All arguments to the function call must be in the order specified
%   above, i.e. printAxis(axisLabel,xData,yData,color,limits) would not
%   work.  If an optional input is excluded, inputs to the right should be
%   shifted to the left to replace them.

xLabel = [];
yLabel = [];
limits = [];
color = 'b';
clearFlag = 0;

% 
% PARSE INPUTS
%
if nargin < 3                                                              % You must have three inputs
    error('Too few input arguments:  axis, xData, and yData required');    % ^
elseif nargin == 3                                                         % Just three inputs, handle and x and y data
    axisLabel = varargin{1};                                               % ^
    xData = varargin{2};                                                   % ^
    yData = varargin{3};                                                   % ^
elseif nargin == 4                                                         % With four inputs first three handle, x, y ...
    axisLabel = varargin{1};                                               % ^
    xData = varargin{2};                                                   % ^
    yData = varargin{3};                                                   % ^
    if ischar(varargin{4})                                                 % ... fourth can be color
        color = varargin{4};                                               % ^
    elseif ( size(varargin{4},2) > 1 )                                     % ... or limtis
        limits = varargin{4};                                              % ^
    else                                                                   % ... or clearFlag
        clearFlag = varargin{4};                                           % ^
    end                                                                    % ^
elseif nargin == 5                                                         % With five inputs first three handle, x, y ...
    axisLabel = varargin{1};                                               % ^
    xData = varargin{2};                                                   % ^
    yData = varargin{3};                                                   % ^
    if ( size(varargin{4},2) > 1 && ~ischar(varargin{4}) )                  % ... fourth can be limits ...
        limits = varargin{4};                                              % ^
        if ischar(varargin{5})                                             % ...... in which case fifth can be color ...
            color = varargin{5};                                           % ^
        else                                                               % ...... or clearFlag
            clearFlag = varargin{5};                                       % ^
        end                                                                % ^
    elseif ischar(varargin{5})                                             % ... or xLabel then yLabel                                                
        xLabel = varargin{4};                                              % ^
        yLabel = varargin{5};                                              % ^
    else                                                                   % ... or color then clearFlag
        color = varargin{4};                                               % ^
        clearFlag = varargin{5};                                           % ^
    end                                                                    % ^
elseif nargin == 6                                                         % With six inputs first three handle, x, y ...
    axisLabel = varargin{1};                                               % ^
    xData = varargin{2};                                                   % ^
    yData = varargin{3};                                                   % ^
    if ( size(varargin{4},2) > 1 && ~ischar(varargin{4}) )                  % ... fourth can be limits, and five six are color and clearFlag
        limits = varargin{4};                                              % ^
        color = varargin{5};                                               % ^
        clearFlag = varargin{6};                                           % ^
    else                                                                   % ... or fourth and fifth are xLabel and yLabel ...
        xLabel = varargin{4};                                              % ^
        yLabel = varargin{5};                                              % ^
        if ischar(varargin{6})                                             % ...... in which case sixth can be color
            color = varargin{6};                                           % ^
        elseif ( size(varargin{6},2) > 1 )                                 % ...... or limits
            limits = varargin{6};                                          % ^
        else                                                               % ...... or clearFlag
            clearFlag = varargin{6};                                       % ^
        end                                                                % ^
    end                                                                    % ^
elseif nargin == 7                                                         % With seven inputs first five must be handle, x, y, xLabel, yLabel ...
    axisLabel = varargin{1};                                               % ^
    xData = varargin{2};                                                   % ^
    yData = varargin{3};                                                   % ^
    xLabel = varargin{4};                                                  % ^
    yLabel = varargin{5};                                                  % ^
    if ( size(varargin{6},2) > 1 && ~ischar(varargin{6}) )                  % ... sixth can be limits ...
        limits = varargin{6};                                              % ^
        if ischar(varargin{7})                                             % ...... in which case seventh can be color
            color = varargin{7};                                           % ^
        else                                                               % ...... or clearFlag
            clearFlag = varargin{7};                                       % ^
        end                                                                % ^
    else                                                                   % ...or sixth and seventh can be color and clearFlag
        color = varargin{6};                                               % ^
        clearFlag = varargin{7};                                           % ^
    end                                                                    % ^                                       
elseif nargin == 8                                                         % Maximum of eight inputs
    axisLabel = varargin{1};                                               % ^
    xData = varargin{2};                                                   % ^
    yData = varargin{3};                                                   % ^
    xLabel = varargin{4};                                                  % ^
    yLabel = varargin{5};                                                  % ^
    limits = varargin{6};                                                  % ^
    color = varargin{7};                                                   % ^
    clearFlag = varargin{8};                                               % ^
end                                                                        % ^

%
% PLOT DATA
%
len = numel(xData);                                                        % Determine time for plot
tEnd = xData(len);                                                         % ^
if tEnd < 200                                                              % ^
    tStart = 0;                                                            % ^
else                                                                       % ^
    tStart = tEnd - 200;                                                   % ^
end                                                                        % ^
if clearFlag == 1                                                          % Clear the previous graph if requested, dont by default
    hold(axisLabel,'off');                                                 % ^
    cla(axisLabel)                                                         % ^
end                                                                        % ^
plot(axisLabel,xData,yData,color);                                         % Plot the data to current axis
if ~isempty(xLabel)                                                        % Give labels if they exist
    xlabel(axisLabel,xLabel);                                              % ^
    ylabel(axisLabel,yLabel);                                              % ^
end                                                                        % ^
if numel(limits) == 2                                                      % Handle limits
    axis(axisLabel,[ tStart tEnd limits ]);                                % ^
elseif numel(limits) == 4                                                  % ^
    axis(axisLabel,limits);                                                % ^
end
hold(axisLabel,'on');

%
% DISPLAY TEXT ON AXIS
%
xPos = 0.05*(tEnd - tStart) + tStart;
yLim = ylim(axisLabel);
yPos = 0.9*(yLim(2) - yLim(1)) + yLim(1);
text(xPos,yPos,num2str(yData(len),'%0.2f'),'Parent',axisLabel,'BackgroundColor',[.7 .9 .7],'FontSize',14);

end                                                                        % END FUNCTION

