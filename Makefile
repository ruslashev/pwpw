src = main.cc
cflags = -g -std=c++17 \
         -Wall -Wextra -Wduplicated-cond -Wformat=2 -Wduplicated-branches -Wdouble-promotion -Wvla \
         -Wnull-dereference -Wdisabled-optimization -Wlogical-op -Wtrampolines -Wpointer-arith \
         -Wundef -Wmissing-format-attribute -Wmissing-format-attribute -Wredundant-decls -Wpadded \
         -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-padded
bin = pwpw
builddir = .build

obj = $(src:%.cc=$(builddir)/obj/%.o)
deps = $(src:%.cc=$(builddir)/dep/%.d)
depcflag = -MD -MP -MF $(@:$(builddir)/obj/%.o=$(builddir)/dep/%.d)

cxx = g++

all: $(bin)
	./$(bin)

$(bin): $(obj)
	@echo "cxx $(@F)"
	@$(cxx) $< -o $@

$(obj): | $(builddir)

$(builddir)/obj/%.o: %.cc
	@echo "cxx $(<F)"
	@$(cxx) $(cflags) $< -o $@ -c $(depcflag)

$(builddir):
	@mkdir -p $(builddir)/obj
	@mkdir -p $(builddir)/dep

clean:
	@echo "clean all"
	@rm -rf $(builddir) $(bin)

-include $(deps)

