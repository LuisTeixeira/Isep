isLista(X):-var(X),!,fail.
isLista([]).
isLista([_|_]).