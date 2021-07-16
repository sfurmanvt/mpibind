from mpibind import _ffi, _libmpibind

if __name__ == "__main__":
  p_handle = _ffi.new("struct mpibind_t **")
  _libmpibind.mpibind_init(p_handle)
  handle = p_handle[0]
  _libmpibind.mpibind_set_ntasks(handle, 4)
  _libmpibind.mpibind(handle)
  _libmpibind.mpibind_mapping_print(handle)
  print("I am in temp file") 