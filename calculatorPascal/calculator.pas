program Calculator;

uses
  SysUtils;

var
  x, y, result: real;
  operation: char;

begin
  write('Write first number: ');
  readln(x);
  
  write('Write operator(-, +, *, /): ');
  readln(operation);
  
  write('Write second number: ');
  readln(y);
  
  case operation of
    '+': result := x + y;
    '-': result := x - y;
    '*': result := x * y;
    '/': result := x / y
  end;
  
  writeln('Result: ', x:0:2, ' ', operation, ' ', y:0:2, ' = ', result:0:2);
end.