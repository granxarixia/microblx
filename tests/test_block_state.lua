--
-- Test the ubx.block_tostate function
--

local luaunit=require("luaunit")
local ffi=require("ffi")
local ubx=require("ubx")

local assert_equals = luaunit.assert_equals

local nd=ubx.node_create("testnode")

ubx.load_module(nd, "stdtypes")
ubx.load_module(nd, "random")

ubx.ffi_load_types(nd)

local b = ubx.block_create(nd, "ubx/random",
			   "b", {min_max_config={min=32, max=127}})

function test_switch_block_inactive()
   ubx.block_tostate(b, 'inactive')
   assert_equals(b.block_state, ffi.C.BLOCK_STATE_INACTIVE)
end

function test_switch_block_preinit()
   ubx.block_tostate(b, 'preinit')
   assert_equals(b.block_state, ffi.C.BLOCK_STATE_PREINIT)
end

function test_switch_block_active()
   ubx.block_tostate(b, 'active')
   assert_equals(b.block_state, ffi.C.BLOCK_STATE_ACTIVE)
end

function test_switch_block_preinit()
   ubx.block_tostate(b, 'preinit')
   assert_equals(b.block_state, ffi.C.BLOCK_STATE_PREINIT)
end


os.exit( luaunit.LuaUnit.run() )
