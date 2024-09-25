program rectangle;

var
	height, width, i, n: integer;

begin
	height := 5;
	width := 7;

	for i := 1 to width do
	begin
		write('* ');
	end;
	writeln;

	for i := 1 to height - 2 do
	begin
		write('*');

		for n := 1 to width - 1 do
		begin
			write('  ');
		end;

		write('*');
		writeln;
	end;
 
	for i := 1 to width do
	begin
		write('* ');
	end;
	writeln;
end.