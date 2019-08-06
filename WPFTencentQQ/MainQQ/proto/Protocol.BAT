echo on

set Path=ProtoGen\protogen.exe

 
%Path%  -i:CallArgus.proto    -o:..\Common\CallArgus.cs

set Path=protoc.exe

%Path% --cpp_out=. CallArgus.proto

pause