################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
device/%.obj: ../device/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/NIT Calicut/My NITC M.Tech Project/Second Semester Project/MY TMS320F28379D Code/Code_for_Lab_of_DCPEC/Code_for_Lab_of_DCPEC" --include_path="C:/ti/C2000Ware_4_00_00_00/driverlib/f2837xd/driverlib" --include_path="D:/NIT Calicut/My NITC M.Tech Project/Second Semester Project/MY TMS320F28379D Code/Code_for_Lab_of_DCPEC/Code_for_Lab_of_DCPEC/device" --include_path="C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=_DUAL_HEADERS --define=_FLASH --define=CPU1 --define=DEBUG -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="device/$(basename $(<F)).d_raw" --obj_directory="device" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


