# Makefile

#------------------------------------------------------#

# Location definitions

# Location of source code files
SRCDIR = src
# Location of generated .o files
BUILDDIR = build
# Name of executable to create
EXEC = Vote_Counter

#------------------------------------------------------#

# Denotes the list of source files to compile, all C++ files
FILES = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*.cc) $(wildcard $(SRCDIR)/*.cxx)

# Denotes header files to include
HEADERS = $(wildcard $(SRCDIR)/*.h)

# Extracts only the filenames; strips off the directory with notdir and strips off the extension with basename
FILEBASES = $(basename $(notdir $(FILES)))

# Denotes the generated object files in their directory from the source files using a string substitution
# Adds the .o suffix to base filenames to denote object files
# Adds build directory as prefix
OFILES = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(FILEBASES)))

# Add -Idirname to add directories to the compiler search path for finding .h files
INCLUDEDIRS = -I$(SRCDIR)

#------------------------------------------------------#

# Macros

# Use g++ compiler for C++ files
G = g++

# Compile with all warnings, using C++ 14
# Also links .o files into executable
LFLAG = -std=c++14 -Wall
# Compile .c files to generate .o files
# Include h files
CFLAG = $(LFLAG) $(INCLUDEDIRS) -c

#------------------------------------------------------#

# Recipes
# makefile format is:
#
# target: prerequisites
#	recipe


# To make everything, ensure that the build directory exists and the executables exists
all: $(BUILDDIR) $(EXEC)

# Make Vote_Counter (main) executable
# $^ Means everything in the prerequisites, $@ means the target
# Ensure that the build directory exists
$(EXEC): $(OFILES)
	@printf "\n=== Linking into $@. ===\n"
	$G $(LFLAG) $^ -o $@

# Says that each .o file depends on the presence of the build directory
$(OFILES): | $(BUILDDIR)

# Ensure the build directory is created. -p flag means mkdir only if the directory doesn't exist yet
$(BUILDDIR):
	@printf "\n=== Making build directory for object files ===\n"
	mkdir -p build

#------------------------------------------------------#

# To generate the build/*.o files, first match the % in the o file with the equivalent in its C++ file to ensure they have the same name and a 1-1 generation (without it, node.c would compile into node.o and votecount.o for instance)
# As before, % matches substring. For the o file to be made, its build/*.o must exist, and that can only be made if its corresponding C++ file exists
# Make auto-dependencies to recompile if an h file is changed by calling the MAKE_DEPEND function
$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	@printf "\n=== Generating auto-dependencies for $<. ===\n"
	$(call MAKE_DEPEND, $<, $@, $(subst .o,.d,$@))
	@printf "\n=== Compiling $< into $@. ===\n"
	$G $(CFLAG) $< -o $@

# Do same for cc and cxx files
$(BUILDDIR)/%.o : $(SRCDIR)/%.cxx
	@printf "\n=== Generating auto-dependencies for $<. ===\n"
	$(call MAKE_DEPEND, $<, $@, $(subst .o,.d,$@))
	@printf "\n=== Compiling $< into $@. ===\n"
	$G $(CFLAG) $< -o $@
$(BUILDDIR)/%.o : $(SRCDIR)/%.cc
	@printf "\n=== Generating auto-dependencies for $<. ===\n"
	$(call MAKE_DEPEND, $<, $@, $(subst .o,.d,$@))
	@printf "\n=== Compiling $< into $@. ===\n"
	$G $(CFLAG) $< -o $@

#------------------------------------------------------#

# Make auto-generated dependencies to recompile an object file if h file is changed
# Usage: $(call make-depend, source-file, object-file, depend-file)
MAKE_DEPEND = $G -MM -MF $3 -MP -MT $2 $(CFLAG) $1

# Once the .d files are made for dependencies, load them into make as if the rules were written in this file using the "-include" command
-include $(OFILES:.o=.d)

#------------------------------------------------------#

# Remove generated .o files and executable
clean:
	@printf "=== Removing $(EXEC) executable ===\n"
	rm -f $(EXEC)
	@printf "\n=== Removing generated report ===\n"
	rm -f $(wildcard *Report.*)
	@printf "\n=== Removing build directory ===\n"
	rm -rf $(BUILDDIR)
	@printf "\n=== Removing $(TESTEXEC) executable ===\n"
	rm -f $(TESTEXEC)

#------------------------------------------------------#

# Unit tests

TESTDIR	= tests

TESTEXEC = $(TESTDIR)/Unit_Tests

TFILES = $(wildcard $(TESTDIR)/*.cpp) $(wildcard $(TESTDIR)/*.cc) $(wildcard $(TESTDIR)/*.cxx)

TOFILES = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(notdir $(TFILES)))))

# Pretty much copy same recipes from regular executables
tests: $(BUILDDIR) $(TESTEXEC)

# Need to link regular OFILES as well, but filter out main to prevent multiple definition conflicts
$(TESTEXEC): $(TOFILES) $(filter-out $(BUILDDIR)/main.o, $(OFILES))
	@printf "\n=== Linking into $@. ===\n"
	$G $(LFLAG) $^ -o $@

$(TOFILES): | $(BUILDDIR)

$(BUILDDIR)/%.o : $(TESTDIR)/%.cpp
	@printf "\n=== Generating auto-dependencies for $<. ===\n"
	$(call MAKE_DEPEND, $<, $@, $(subst .o,.d,$@))
	@printf "\n=== Compiling $< into $@. ===\n"
	$G $(CFLAG) $< -o $@
$(BUILDDIR)/%.o : $(TESTDIR)/%.cxx
	@printf "\n=== Generating auto-dependencies for $<. ===\n"
	$(call MAKE_DEPEND, $<, $@, $(subst .o,.d,$@))
	@printf "\n=== Compiling $< into $@. ===\n"
	$G $(CFLAG) $< -o $@
$(BUILDDIR)/%.o : $(TESTDIR)/%.cc
	@printf "\n=== Generating auto-dependencies for $<. ===\n"
	$(call MAKE_DEPEND, $<, $@, $(subst .o,.d,$@))
	@printf "\n=== Compiling $< into $@. ===\n"
	$G $(CFLAG) $< -o $@
