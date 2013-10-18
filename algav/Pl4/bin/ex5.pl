temRepetidos([H|[]],false)
%temRepetidos([H|[H2|[]]):-H.
%temRepetidos([H|T],Repetidos):-