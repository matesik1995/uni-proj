ostatni([X],X).
ostatni([_|T],X):-ostatni(T,X).

oproczost([_],[]).
oproczost([H|T],X):-oproczost(T,Y),X=[H|Y].

odwroc([A],[A]).
odwroc([H|T],R):-odwroc(T,X),append(X,[H],R).

srodek([H],H).
srodek([_|T],X):-oproczost(T,Y),srodek(Y,X).

rosnaca([_]).
rosnaca([H1,H2|T]):-H1<H2, rosnaca([H2|T]).

maxlist([X],X).
maxlist([H|T],X):-maxlist(T,X), X>H.
maxlist([H|T],H):-maxlist(T,X), X=<H.


ileelem([_],X):- X is 1.
ileelem([_|T],Y):-ileelem(T,X), Y is X+1.

suma([X],X).
suma([H|T],Y):-suma(T,X), Y is X+H.

srednia(L,S):- suma(L, Sum), ileelem(L, Elem), S is Sum/Elem.

subsetord([],[_]).
subsetord(H,[H|_]).
subsetord([H1|T1],[H2|T2]):-H1=H2, subsetord(T1,T2).
subsetord([H1|T1],[H2|T2]):-H1\=H2, subsetord([H1|T1],T2).

subsum([],0,[]).
subsum([H|T],R,[H|L]):-A is R-H, subsum(T,A,L).
subsum([_|T],R,L):-subsum(T,R,L).

roznica([],[],[]).
roznica([H1|T1],[H2|T2],[X|R]):-X is H2-H1, roznica(T1,T2,R).


diffset([],[_],[]).
diffset([H|T],L,X):-member(H,L),!,diffset(T,L,X).
diffset([H|T],L,[H|X]):-diffset(T,L,X).

sign(X,plus):-X>0,!.
sign(X,minus):-X<0,!.
sign(_,zero).

silnia(0,1).
silnia(Y,X):-Y>0, Y1 is Y-1, silnia(Y1,X1), X is Y*X1.


doposort(X,[],[X]).
doposort(X,[H|T],[H|W]):-X>=H,
	doposort(X,T,W).
doposort(X,[H|T],[H,X|T]):-H<X.

insertsort([],[]).
insertsort([H|T],X):-insertsort(T,S),doposort(H,S,X).


swap([],[]).
swap([H1,H2|T],[H2,H1|T]):- H1>H2.
swap([H1,H2|T],[H1,H2|S]):- H1=<H2, swap(T,S).

bubble(L,S):-swap(L,S), L=S, !.
bubble(L,S):-swap(L,S), L\=S, bubble(L,S).
