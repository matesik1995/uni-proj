%podzial(lista,liczniki,W);


odc(0,X,[],X).
odc(N,[H|T],[H|S],X):-N>0, N1 is N-1, odc(N1,T,S,X).

podzial(_,[],[]).
podzial(X,[H|T],[F|W]):- podzial(G,T,W), odc(H,X,F,G).


zlicz([],_,[],[]).
zlicz([H|T],[A,B],[H|W1],W2):-H>A, H<B, zlicz(T,[A,B],W1,W2),!.
zlicz([H|T],[A,B],W1,[H|W2]):-zlicz(T,[A,B],W1,W2).


doposort(X,[],[X]).
doposort(X,[H|T],[H|W]):-H<X,doposort(X,T,W).
doposort(X,[H|T],[X,H|T]):-H>=X.


kolejka(0,[0]).
kolejka(X,[X|T]):-X1 is X-1, kolejka(X1,T).


czyn(1,2,[]).
czyn(X,Y,[Y|T]):-pierwsza(Y),dzielnik(X,Y),!,X1 is X/Y, czyn(X1,2,T).
czyn(X,Y,T):-X>=Y, Y1 is Y+1, czyn(X,Y1,T).

czynniki(X,W):-czyn(X,2,W).


pom(_,1,[]):-!.
pom(X,Y,[Y|T]):- X mod Y =:= 0,!, Y1 is Y-1, pom(X,Y1,T).
pom(X,Y,T):- Y1 is Y-1,pom(X,Y1,T).

dzielniki(X,W):-pom(X,X,W).

pierwsza(X):-X1 is X-1, pier(X,X1).
pier(_,1).
pier(X,Y):-Y>1, dzielnik(X,Y),!,false.
pier(X,Y):-Y>1, Y1 is Y-1, pier(X,Y1).

dzielnik(N,X):- N mod X =:= 0.


swap([],[]).
swap([X,Y|T],[Y,X|T]):- X>Y.
swap([X,Y|T],[X|T2]):- X=<Y, swap([Y|T],T2).

babel(X,Y):- swap(X,N),!, babel(N,Y).
babel(X,X).
