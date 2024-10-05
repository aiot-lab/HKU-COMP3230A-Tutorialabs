# A Minimalistic Makefile
.PHONY: all

# rename with your uid, make sure no space after your uid
UID = [UID]

# Default target
all: prepare inference main

# download file if not found in the folder
prepare:
	@if [ ! -f model.bin ]; then \
		wget -O model.bin https://huggingface.co/huangs0/smollm/resolve/main/model.bin; \
	fi
	@if [ ! -f tokenizer.bin ]; then \
		wget -O tokenizer.bin https://huggingface.co/huangs0/smollm/resolve/main/tokenizer.bin; \
	fi

inference:
	gcc -o inference inference_$(UID).c -O3 -lm

main:
	gcc -o main main_$(UID).c

# Clean target to remove the downloaded file
clean:
	rm -f run main inference

clean_bin:
	rm -f model.bin tokenizer.bin