src = main.cc wm.cc renderer.cc opengl.cc simulation.cc mainloop.cc camera.cc
cflags = -g -std=c++17 \
         -Wall -Wextra -Wduplicated-cond -Wformat=2 -Wduplicated-branches -Wdouble-promotion -Wvla \
         -Wnull-dereference -Wdisabled-optimization -Wlogical-op -Wtrampolines -Wpointer-arith \
         -Wundef -Wmissing-format-attribute -Wmissing-format-attribute -Wredundant-decls -Wpadded \
         -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-padded
lflags = $(shell pkg-config --libs glfw3 epoxy)
bin = pwpw
builddir = .build

obj = $(src:%.cc=$(builddir)/obj/%.o)
deps = $(src:%.cc=$(builddir)/dep/%.d)
depcflag = -MD -MP -MF $(@:$(builddir)/obj/%.o=$(builddir)/dep/%.d)

cxx = g++

all: $(bin)
	./$(bin)

$(bin): $(obj)
	@echo "ld $(@F)"
	@$(cxx) $^ -o $@ $(lflags)

$(obj): | $(builddir)

$(builddir)/obj/%.o: %.cc
	@echo "cxx $(<F)"
	@$(cxx) $< -o $@ -c $(depcflag) $(cflags)

$(builddir):
	@mkdir -p $(builddir)/obj
	@mkdir -p $(builddir)/dep

clean:
	@echo "clean all"
	@rm -rf $(builddir) $(bin)

-include $(deps)

