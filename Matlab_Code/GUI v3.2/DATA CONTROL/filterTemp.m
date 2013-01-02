function filterTempOut = filterTemp( tempIn , filterTempIn )

nr = size(tempIn,1);
beta = 0.95;

if nr < 2
    filterTempOut = tempIn;
else
    filterTempOut = [filterTempIn; (1-beta)*tempIn(nr,:)+beta*filterTempIn(nr-1,:)];
end

end

