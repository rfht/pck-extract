#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTR	1024

int main (int argc, char **argv) {
	if (argc != 2 || !strncmp(argv[1], "-h", MAXSTR)) {
		printf("Usage: %s <godot-executable>\n", argv[0]);
		return argc != 2;
	}

	FILE *fp = fopen(argv[1], "r");
	if (!fp) {
		printf("Could not open file '%s'\n", argv[1]);
		return 1;
	}

	fseek(fp, 0L, SEEK_END);
	long ilength = ftell(fp);
	if (ilength <= 0) {
		printf("Truncated file?\n");
		fclose(fp);
		return 1;
	}
	size_t length = ilength;
	fseek(fp, 0L, SEEK_SET);	// rewind
	char *buf = malloc(length);
	if (!buf) {
		printf("Memory allocation failed\n");
		fclose(fp);
		return 1;
	}
	if (fread(buf, 1, length, fp) != length) {
		printf("Input failure (%s)\n", argv[1]);
		fclose(fp);
		return 1;
	}
	fclose(fp);

	int success = 0;
	for (; length >= 4 && !(success=memcmp(buf, "GDPC", 4)); length--, buf++);
	if (!success) {
		printf("Truncated or bad file?\n");
		return 1;
	}

	size_t l = strlen(argv[1]);
	static char fbuf[MAXSTR];
	snprintf(fbuf, sizeof(fbuf), "%s.pck", argv[1]);
	FILE *ofp = fopen(fbuf, "w");
	if (!ofp) {
		printf("Could not create file '%s'\n", fbuf);
		return 1;
	}
	if (fwrite(buf, 1, length, ofp) != length) {
		printf("Output failure (%s)\n", fbuf);
		return 1;
	}
	printf("All done! Your file is in '%s'.\n", fbuf);
}
