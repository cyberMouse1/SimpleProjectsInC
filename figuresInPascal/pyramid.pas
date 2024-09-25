program Pyramid;

var
    height, i, j: integer;

begin
    write('Enter height: ');
    readln(height);

	for i := 1 to height do
    begin
		for j := 1 to height - i do
		begin
			write(' ');
		end;
		for j := 1 to 2*i - 1 do
		begin
			write('*');
		end;
		writeln;
	end;
end.
