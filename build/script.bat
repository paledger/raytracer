@Echo Off

echo "Hello, World."

for %%i in (..\tests\p2\*.args) do CALL raytrace type %%i
