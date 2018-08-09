%decimal to binary
dTb(0,[]):-!.
dTb(X,[H|T]):-H is X mod 2, X1 is X//2, dTb(X1,T).

%binary to decimal
bTd([],0,0):-!.
bTd([H|T],N,X):-bTd(T,N1,X1), X is X1+H*2**N1, N is N1+1.
bTd(T,X):-bTd(T,_,X).

%remove repeating digits
rem([X],[X]):-!.
rem([X,Y|T],[X|R]):-X=\=Y,!,rem(T,R).
rem([_|T],N):-rem(T,N).

swap([X,Y|T],[Y,X|T]):-
	dTb(X,X1), dTb(Y,Y1),
	rem(X1,X2), rem(Y1,Y2),
	bTd(X2,A), bTd(Y2,B),
	A>B,!.
swap([X|T],[X|N]):-swap(T,N).

bubble(X,Y):-swap(X,N),!,bubble(N,Y).
bubble(X,X).
