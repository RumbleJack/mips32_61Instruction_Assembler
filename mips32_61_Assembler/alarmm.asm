.data
#	.p2align	2
h:
	.4byte	1                       # 0x1
#	.size	h, 4

#	.type	m,@object               # @m
#	.p2align	2
m:
	.4byte	2                       # 0x2
#	.size	m, 4

#	.type	s,@object               # @s
#	.p2align	2
s:
	.4byte	3                       # 0x3
#	.size	s, 4

#	.type	c,@object               # @c
#	.p2align	2
c:
	.4byte	4                       # 0x4
#	.size	c, 4

#	.type	time,@object            # @time
#	.p2align	2
time:
	.4byte	5                       # 0x5
#	.size	time, 4

#	.type	alarm_h,@object         # @alarm_h
#	.p2align	2
alarm_h .4byte	6                       # 0x6
#	.size	alarm_h, 4

#	.type	alarm_m,@object         # @alarm_m
#	.p2align	2
alarm_m:
	.4byte	7                       # 0x7
#	.size	alarm_m, 4

#	.type	alarm_s,@object         # @alarm_s
#	.p2align	2
alarm_s:
	.4byte	8                       # 0x8
#	.size	alarm_s, 4

#	.type	alarm_mode,@object      # @alarm_mode
#	.p2align	2
alarm_mode:
	.4byte	9                       # 0x9
#	.size	alarm_mode, 4

#	.type	select_loc,@object      # @select_loc
#	.p2align	2
select_loc:
	.4byte	10                      # 0xa
#	.size	select_loc, 4


#	.ident	"clang version 3.9.1 (tags/RELEASE_391/final)"
#	.section	".note.GNU-stack","",@progbits

	.text
#	.abicalls
#	.option	pic0
#	.nan	legacy
#	.p2align	2
#	.type	delay,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	delay
delay:                                  # @delay
	#.frame	$fp,8 8,$ra
	#.mask 	0x40000000,-4
	addiu $sp, $sp, -8
	#sw $30, 4($sp)
	addiu	$sp, $sp, -8
	#sw	$fp, 4($sp)             # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$2, delay #%hi(c)
	ori	$1, $zero, 40000
	j	$BB0_2
	#sw	$1, %lo(c)($2)
$BB0_1:                                 # %while.body
                                        #   in Loop: Header=BB0_2 Depth=1
	lw	$1, %lo(c)($2)
	addiu	$1, $1, -1
	#sw	$1, %lo(c)($2)
$BB0_2:                                 # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	lw	$1, %lo(c)($2)
	#bnez	$1, $BB0_1
	nop
# BB#3:                                 # %while.end
	or	$sp, $fp, $zero
	lw	$fp, 4($sp)             # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 8
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	delay

#	.p2align	2
#	.type	get_real_time,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	get_real_time
get_real_time:                          # @get_real_time
	#.frame	$fp,8 8,$ra
	#.mask 	0x40000000,-4
	addiu $sp, $sp, -8
	##sw $30 4($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -8
	#sw	$fp, 4($sp)             # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$1, %hi(m)
	lw	$1, %lo(m)($1)
	sll	$2, $1, 2
	sll	$3, $1, 5
	subu	$2, $3, $2
	lui	$3, %hi(h)
	lw	$3, %lo(h)($3)
	sll	$1, $1, 7
	subu	$1, $1, $2
	sll	$2, $3, 4
	sll	$4, $3, 8
	subu	$2, $4, $2
	sll	$4, $3, 11
	subu	$2, $4, $2
	sll	$3, $3, 13
	addu	$2, $3, $2
	addu	$1, $2, $1
	lui	$2, %hi(s)
	lw	$2, %lo(s)($2)
	lui	$3, %hi(time)
	addu	$1, $1, $2
	#sw	$1, %lo(time)($3)
	or	$sp, $fp, $zero
	lw	$fp, 4($sp)             # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 8
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	get_real_time

#	.p2align	2
#	.type	get_alarm_time,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	get_alarm_time
get_alarm_time:                         # @get_alarm_time
	#.frame	$fp,8 8,$ra
	#.mask 	0x40000000,-4
	addiu $sp, $sp, -8
	#sw $30 4($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -8
	#sw	$fp, 4($sp)             # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$1, %hi(alarm_m)
	lw	$1, %lo(alarm_m)($1)
	sll	$2, $1, 2
	sll	$3, $1, 5
	subu	$2, $3, $2
	lui	$3, %hi(alarm_h)
	lw	$3, %lo(alarm_h)($3)
	sll	$1, $1, 7
	subu	$1, $1, $2
	sll	$2, $3, 4
	sll	$4, $3, 8
	subu	$2, $4, $2
	sll	$4, $3, 11
	subu	$2, $4, $2
	sll	$3, $3, 13
	addu	$2, $3, $2
	addu	$1, $2, $1
	lui	$2, %hi(alarm_s)
	lw	$2, %lo(alarm_s)($2)
	lui	$3, %hi(time)
	addu	$1, $1, $2
	#sw	$1, %lo(time)($3)
	or	$sp, $fp, $zero
	lw	$fp, 4($sp)             # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 8
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	get_alarm_time

#	.p2align	2
#	.type	get_time,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	get_time
get_time:                               # @get_time
	#.frame	$fp,8 24,$ra
	#.mask 	0xc0000000,-4
	addiu $sp, $sp, -24
	#sw $31 20($sp)
	#sw $30 16($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -24
	#sw	$ra, 20($sp)            # 4-byte Folded Spill
	#sw	$fp, 16($sp)            # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$1, %hi(alarm_mode)
	lw	$1, %lo(alarm_mode)($1)
	#beqz	$1, $BB3_2
	nop
# BB#1:                                 # %if.then
	jal	get_real_time
	nop
	j	$BB3_3
	nop
$BB3_2:                                 # %if.else
	jal	get_alarm_time
	nop
$BB3_3:                                 # %if.end
	or	$sp, $fp, $zero
	lw	$fp, 16($sp)            # 4-byte Folded Reload
	lw	$ra, 20($sp)            # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 24
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	get_time

#	.p2align	2
#	.type	increase_time,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	increase_time
increase_time:                          # @increase_time
	#.frame	$fp,8 8,$ra
	#.mask 	0x40000000,-4
	addiu $sp, $sp, -8
	#sw $30 4($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -8
	#sw	$fp, 4($sp)             # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$2, %hi(s)
	lw	$1, %lo(s)($2)
	slti	$1, $1, 59
	#beqz	$1, $BB4_2
	nop
# BB#1:                                 # %if.then
	lw	$1, %lo(s)($2)
	addiu	$1, $1, 1
	j	$BB4_5
	#sw	$1, %lo(s)($2)
$BB4_2:                                 # %if.else
	#sw	$zero, %lo(s)($2)
	lui	$2, %hi(m)
	lw	$1, %lo(m)($2)
	slti	$1, $1, 59
	#beqz	$1, $BB4_4
	nop
# BB#3:                                 # %if.then2
	lw	$1, %lo(m)($2)
	addiu	$1, $1, 1
	j	$BB4_5
	#sw	$1, %lo(m)($2)
$BB4_4:                                 # %if.else4
	#sw	$zero, %lo(m)($2)
	lui	$1, %hi(h)
	lw	$2, %lo(h)($1)
	addiu	$2, $2, 1
	#sw	$2, %lo(h)($1)
$BB4_5:                                 # %if.end6
	or	$sp, $fp, $zero
	lw	$fp, 4($sp)             # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 8
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	increase_time

#	.p2align	2
#	.type	increase_alarm_s,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	increase_alarm_s
increase_alarm_s:                       # @increase_alarm_s
	#.frame	$fp,8 8,$ra
	#.mask 	0x40000000,-4
	addiu $sp, $sp, -8
	#sw $30 4($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -8
	#sw	$fp, 4($sp)             # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$2, %hi(alarm_s)
	lw	$1, %lo(alarm_s)($2)
	slti	$1, $1, 59
	#beqz	$1, $BB5_2
	nop
# BB#1:                                 # %if.then
	lw	$1, %lo(alarm_s)($2)
	addiu	$1, $1, 1
	j	$BB5_3
	#sw	$1, %lo(alarm_s)($2)
$BB5_2:                                 # %if.else
	#sw	$zero, %lo(alarm_s)($2)
$BB5_3:                                 # %if.end
	or	$sp, $fp, $zero
	lw	$fp, 4($sp)             # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 8
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	increase_alarm_s

#	.p2align	2
#	.type	increase_alarm_m,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	increase_alarm_m
increase_alarm_m:                       # @increase_alarm_m
	#.frame	$fp,8 8,$ra
	#.mask 	0x40000000,-4
	addiu $sp, $sp, -8
	#sw $30 4($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -8
	#sw	$fp, 4($sp)             # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$2, %hi(alarm_m)
	lw	$1, %lo(alarm_m)($2)
	slti	$1, $1, 59
	#beqz	$1, $BB6_2
	nop
# BB#1:                                 # %if.then
	lw	$1, %lo(alarm_m)($2)
	addiu	$1, $1, 1
	j	$BB6_3
	#sw	$1, %lo(alarm_m)($2)
$BB6_2:                                 # %if.else
	#sw	$zero, %lo(alarm_m)($2)
$BB6_3:                                 # %if.end
	or	$sp, $fp, $zero
	lw	$fp, 4($sp)             # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 8
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	increase_alarm_m

#	.p2align	2
#	.type	increase_alarm_h,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	increase_alarm_h
increase_alarm_h:                       # @increase_alarm_h
	#.frame	$fp,8 8,$ra
	#.mask 	0x40000000,-4
	addiu $sp, $sp, -8
	#sw $30 4($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -8
	#sw	$fp, 4($sp)             # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$2, %hi(alarm_h)
	lw	$1, %lo(alarm_h)($2)
	slti	$1, $1, 23
	#beqz	$1, $BB7_2
	nop
# BB#1:                                 # %if.then
	lw	$1, %lo(alarm_h)($2)
	addiu	$1, $1, 1
	j	$BB7_3
	#sw	$1, %lo(alarm_h)($2)
$BB7_2:                                 # %if.else
	#sw	$zero, %lo(alarm_h)($2)
$BB7_3:                                 # %if.end
	or	$sp, $fp, $zero
	lw	$fp, 4($sp)             # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 8
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	increase_alarm_h

#	.p2align	2
#	.type	decrease_alarm_s,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	decrease_alarm_s
decrease_alarm_s:                       # @decrease_alarm_s
	#.frame	$fp,8 8,$ra
	#.mask 	0x40000000,-4
	addiu $sp, $sp, -8
	#sw $30 4($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -8
	#sw	$fp, 4($sp)             # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$2, %hi(alarm_s)
	lw	$1, %lo(alarm_s)($2)
	#beqz	$1, $BB8_2
	nop
# BB#1:                                 # %if.then
	lw	$1, %lo(alarm_s)($2)
	addiu	$1, $1, -1
	j	$BB8_3
	#sw	$1, %lo(alarm_s)($2)
$BB8_2:                                 # %if.else
	addiu	$1, $zero, 59
	#sw	$1, %lo(alarm_s)($2)
$BB8_3:                                 # %if.end
	or	$sp, $fp, $zero
	lw	$fp, 4($sp)             # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 8
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	decrease_alarm_s

#	.p2align	2
#	.type	decrease_alarm_m,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	decrease_alarm_m
decrease_alarm_m:                       # @decrease_alarm_m
	#.frame	$fp,8 8,$ra
	#.mask 	0x40000000,-4
	addiu $sp, $sp, -8
	#sw $30 4($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -8
	#sw	$fp, 4($sp)             # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$2, %hi(alarm_m)
	lw	$1, %lo(alarm_m)($2)
	#beqz	$1, $BB9_2
	nop
# BB#1:                                 # %if.then
	lw	$1, %lo(alarm_m)($2)
	addiu	$1, $1, -1
	j	$BB9_3
	#sw	$1, %lo(alarm_m)($2)
$BB9_2:                                 # %if.else
	addiu	$1, $zero, 59
	#sw	$1, %lo(alarm_m)($2)
$BB9_3:                                 # %if.end
	or	$sp, $fp, $zero
	lw	$fp, 4($sp)             # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 8
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	decrease_alarm_m

#	.p2align	2
#	.type	decrease_alarm_h,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	decrease_alarm_h
decrease_alarm_h:                       # @decrease_alarm_h
	#.frame	$fp,8 8,$ra
	#.mask 	0x40000000,-4
	addiu $sp, $sp, -8
	#sw $30 4($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -8
	#sw	$fp, 4($sp)             # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$2, %hi(alarm_h)
	lw	$1, %lo(alarm_h)($2)
	#beqz	$1, $BB10_2
	nop
# BB#1:                                 # %if.then
	lw	$1, %lo(alarm_h)($2)
	addiu	$1, $1, -1
	j	$BB10_3
	#sw	$1, %lo(alarm_h)($2)
$BB10_2:                                # %if.else
	addiu	$1, $zero, 23
	#sw	$1, %lo(alarm_h)($2)
$BB10_3:                                # %if.end
	or	$sp, $fp, $zero
	lw	$fp, 4($sp)             # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 8
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	decrease_alarm_h

#	.p2align	2
#	.type	main,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	main
main:                                   # @main
	#.frame	$fp,8 40,$ra
	#.mask 	0xc0010000,-4
	addiu $sp, $sp, -40
	#sw $31 36($sp)
	#sw $30 32($sp)
	#sw $16 28($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -40
	#sw	$ra, 36($sp)            # 4-byte Folded Spill
	#sw	$fp, 32($sp)            # 4-byte Folded Spill
	#sw	$16, 28($sp)            # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	#sw	$zero, 24($fp)
	addiu	$1, $zero, 1000
	#sw	$1, 20($fp)
	lui	$1, %hi(alarm_mode)
	#sw	$zero, %lo(alarm_mode)($1)
	lui	$1, %hi(select_loc)
	#sw	$zero, %lo(select_loc)($1)
	lui	$16, %hi(time)
$BB11_1:                                # %while.body
                                        # =>This Inner Loop Header: Depth=1
	jal	delay
	nop
	jal	increase_time
	nop
	jal	get_time
	nop
	lw	$1, %lo(time)($16)
	j	$BB11_1
	#sw	$1, 20($fp)
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	main

#	.p2align	2
#	.type	interrupt_0,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	interrupt_0
interrupt_0:                            # @interrupt_0
	#.frame	$fp,8 8,$ra
	#.mask 	0x40000000,-4
	addiu $sp, $sp, -8
	#sw $30 4($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -8
	#sw	$fp, 4($sp)             # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$1, %hi(alarm_mode)
	lw	$2, %lo(alarm_mode)($1)
	sltiu	$2, $2, 1
	#sw	$2, %lo(alarm_mode)($1)
	or	$sp, $fp, $zero
	lw	$fp, 4($sp)             # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 8
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	interrupt_0

#	.p2align	2
#	.type	interrupt_1,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	interrupt_1
interrupt_1:                            # @interrupt_1
	#.frame	$fp,8 8,$ra
	#.mask 	0x40000000,-4
	addiu $sp, $sp, -8
	#sw $30 4($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -8
	#sw	$fp, 4($sp)             # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$1, %hi(select_loc)
	lw	$1, %lo(select_loc)($1)
	slti	$1, $1, 3
	#beqz	$1, $BB13_3
	nop
# BB#1:                                 # %land.lhs.true
	lui	$1, %hi(alarm_mode)
	lw	$1, %lo(alarm_mode)($1)
	#beqz	$1, $BB13_3
	nop
# BB#2:                                 # %if.then
	lui	$1, %hi(select_loc)
	lw	$2, %lo(select_loc)($1)
	addiu	$2, $2, 1
	#sw	$2, %lo(select_loc)($1)
$BB13_3:                                # %if.end
	or	$sp, $fp, $zero
	lw	$fp, 4($sp)             # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 8
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	interrupt_1

#	.p2align	2
#	.type	interrupt_2,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	interrupt_2
interrupt_2:                            # @interrupt_2
	#.frame	$fp,8 8,$ra
	#.mask 	0x40000000,-4
	addiu $sp, $sp, -8
	#sw $30 4($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -8
	#sw	$fp, 4($sp)             # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$1, %hi(select_loc)
	lw	$1, %lo(select_loc)($1)
	#beqz	$1, $BB14_3
	nop
# BB#1:                                 # %land.lhs.true
	lui	$1, %hi(alarm_mode)
	lw	$1, %lo(alarm_mode)($1)
	#beqz	$1, $BB14_3
	nop
# BB#2:                                 # %if.then
	lui	$1, %hi(select_loc)
	lw	$2, %lo(select_loc)($1)
	addiu	$2, $2, -1
	#sw	$2, %lo(select_loc)($1)
$BB14_3:                                # %if.end
	or	$sp, $fp, $zero
	lw	$fp, 4($sp)             # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 8
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	interrupt_2

#	.p2align	2
#	.type	interrupt_3,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	interrupt_3
interrupt_3:                            # @interrupt_3
	#.frame	$fp,8 24,$ra
	#.mask 	0xc0000000,-4
	addiu $sp, $sp, -24
	#sw $31 20($sp)
	#sw $30 16($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -24
	#sw	$ra, 20($sp)            # 4-byte Folded Spill
	#sw	$fp, 16($sp)            # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$1, %hi(alarm_mode)
	lw	$1, %lo(alarm_mode)($1)
	#beqz	$1, $BB15_6
	nop
# BB#1:                                 # %if.then
	lui	$2, %hi(select_loc)
	lw	$1, %lo(select_loc)($2)
	#beqz	$1, $BB15_4
	nop
# BB#2:                                 # %if.else
	lw	$1, %lo(select_loc)($2)
	addiu	$2, $zero, 1
	bne	$1, $2, $BB15_5
	nop
# BB#3:                                 # %if.then3
	jal	increase_alarm_m
	nop
	j	$BB15_6
	nop
$BB15_4:                                # %if.then1
	jal	increase_alarm_s
	nop
	j	$BB15_6
	nop
$BB15_5:                                # %if.else4
	jal	increase_alarm_h
	nop
$BB15_6:                                # %if.end6
	or	$sp, $fp, $zero
	lw	$fp, 16($sp)            # 4-byte Folded Reload
	lw	$ra, 20($sp)            # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 24
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	interrupt_3

#	.p2align	2
#	.type	interrupt_4,@function
#	.set	nomicromips
#	.set	nomips16
#	.ent	interrupt_4
interrupt_4:                            # @interrupt_4
	#.frame	$fp,8 24,$ra
	#.mask 	0xc0000000,-4
	addiu $sp, $sp, -24
	#sw $31 20($sp)
	#sw $30 16($sp)
#	.fmask	0x00000000,0
#	.set	noreorder
#	.set	nomacro
#	.set	noat
# BB#0:                                 # %entry
	addiu	$sp, $sp, -24
	#sw	$ra, 20($sp)            # 4-byte Folded Spill
	#sw	$fp, 16($sp)            # 4-byte Folded Spill
	addiu	$fp, $sp, 0
	lui	$1, %hi(alarm_mode)
	lw	$1, %lo(alarm_mode)($1)
	#beqz	$1, $BB16_6
	nop
# BB#1:                                 # %if.then
	lui	$2, %hi(select_loc)
	lw	$1, %lo(select_loc)($2)
	#beqz	$1, $BB16_4
	nop
# BB#2:                                 # %if.else
	lw	$1, %lo(select_loc)($2)
	addiu	$2, $zero, 1
	bne	$1, $2, $BB16_5
	nop
# BB#3:                                 # %if.then3
	jal	decrease_alarm_m
	nop
	j	$BB16_6
	nop
$BB16_4:                                # %if.then1
	jal	decrease_alarm_s
	nop
	j	$BB16_6
	nop
$BB16_5:                                # %if.else4
	jal	decrease_alarm_h
	nop
$BB16_6:                                # %if.end6
	or	$sp, $fp, $zero
	lw	$fp, 16($sp)            # 4-byte Folded Reload
	lw	$ra, 20($sp)            # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 24
#	.set	at
#	.set	macro
#	.set	reorder
#	.end	interrupt_4

#	.type	h,@object               # @h
	