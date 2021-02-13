% [RES] = shift(MTX, OFFSET)
% 
% Circular shift 2D matrix samples by OFFSET (a [Y,X] 2-vector),
% such that  RES(POS) = MTX(POS-OFFSET).

function res = shift(mtx, offset)

dims = size(mtx);

offset = mod(-offset,dims);
lala = offset(1);
lulu = offset(2);
re = dims(1);
ru = dims(2);
res = [ mtx(lala + 1:re, lulu+1:ru),  ...
          mtx(lala + 1:re, 1:lulu);        ...
        mtx(1:lala, lulu+1:ru),          ...
	  mtx(1:lala, 1:lulu) ];
