package(
  default_visibility = ["//visibility:public"],
)

# Most callers will want to link this, because it provides a main function.
cc_library(
  name = "minunit",
  srcs = ["minunit.c", "minunit-main.c"],
  hdrs = ["minunit.h"],
  testonly = True,
)

cc_library(
  name = "minunit-nomain",
  srcs = ["minunit.c"],
  hdrs = ["minunit.h"],
  testonly = True,
)
