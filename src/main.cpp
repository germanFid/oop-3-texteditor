#include "editor.h"

void run_editor(const char* file_name) {
	Editor e{file_name};	

	int character;
	while (true) {
		character = getch();
		e.process_keypress(character);
	}
}

int main(int argc, char** argv) {
	if (argc == 2) {
		run_editor(argv[1]);
	}

	else
	{
		FILE* f;
		f = fopen(".tmptext", "w");
		
		if (f != NULL)
		{
			fclose(f);
			run_editor(".tmptext");
		}
	}

	return 0;
}
