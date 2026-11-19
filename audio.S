.syntax unified
.cpu cortex-m0plus
.thumb

.section .rodata
.global mp3_data_start
.global mp3_data_end

.align 4
mp3_data_start:
    .incbin "track_piano.mp3"
mp3_data_end:
