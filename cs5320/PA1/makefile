SK = SK-CS21BTECH11061.cpp
VC = VC-CS21BTECH11061.cpp
runSK_FILE = runSK
runVC_FILE = runVC

compile: ./$(SK) ./$(VC)
	g++ -o $(runSK_FILE) $(SK) -lzmq -w
	g++ -o $(runVC_FILE) $(VC) -lzmq -w

runSK: compile
	./$(runSK_FILE)

runVC: compile
	./$(runVC_FILE)

clean:
	rm -f $(runSK_FILE) $(runVC_FILE)