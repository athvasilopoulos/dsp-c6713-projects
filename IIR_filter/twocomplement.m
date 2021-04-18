function y = twocomplement(x)
% function y=twocomplement(x)
% compute 2's complement equivalent of x in 16 bits
% x is a number in [-1,1)

i = find((x<-1) | (x>=1));
if isempty(i) 
 y = floor(32768*x);
 index = find(y < 0);
 y(index) = 65536+y(index);
 return;
else
 disp('error in twocomplement(): floating number must be in [-1,1)');
 return;
end; 
