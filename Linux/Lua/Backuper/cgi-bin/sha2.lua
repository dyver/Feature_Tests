-- SHA-256 code in Lua 5.3; based on the pseudo-code from
-- Wikipedia (http://en.wikipedia.org/wiki/SHA-2)

package.preload.sha2 = function(...)

local string, setmetatable, assert = string, setmetatable, assert

local _ENV = nil

-- Initialize table of round constants
-- (first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311):
local k = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
}

-- Lines marked with (1) can produce results with more than 32 bits.
-- These values should be used only in other lines marked with (1), or
-- in lines marked with (2), which trim their results to 32 bits.

-- no need to trim at 32 bits (results will be trimmed later)
local function rrotate(x, n)
    return ((x >> n) | (x << (32 - n)))                            -- (1)
end

-- transform a string of bytes in a string of hexadecimal digits
local function str2hexa(s)
    return string.gsub(
        s, ".", function(c) return string.format("%02x", string.byte(c)) end
    )
end

-- append the bit '1' to the message
-- append k bits '0', where k is the minimum number >= 0 such that the
-- resulting message length (in bits) is congruent to 448 (mod 512)
-- append length of message (before pre-processing), in bits, as 64-bit
-- big-endian integer
local function preproc(msg, len)
    local extra = -(len + 1 + 8) % 64
    len = string.pack(">i8", 8 * len) -- original len in bits, coded
    msg = msg .. "\128" .. string.rep("\0", extra) .. len
    assert(#msg % 64 == 0)
    return msg
end

local function initH224(H)
    -- (second 32 bits of the fractional parts of the square roots of the
    -- 9th through 16th primes 23..53)
    H[1] = 0xc1059ed8
    H[2] = 0x367cd507
    H[3] = 0x3070dd17
    H[4] = 0xf70e5939
    H[5] = 0xffc00b31
    H[6] = 0x68581511
    H[7] = 0x64f98fa7
    H[8] = 0xbefa4fa4
    return H
end

local function initH256(H)
    -- (first 32 bits of the fractional parts of the square roots of the
    -- first 8 primes 2..19):
    H[1] = 0x6a09e667
    H[2] = 0xbb67ae85
    H[3] = 0x3c6ef372
    H[4] = 0xa54ff53a
    H[5] = 0x510e527f
    H[6] = 0x9b05688c
    H[7] = 0x1f83d9ab
    H[8] = 0x5be0cd19
    return H
end

local function digestblock(msg, i, H)
    -- break chunk into sixteen 32-bit big-endian words w[1..16]
    local w = {string.unpack(">I4I4I4I4I4I4I4I4I4I4I4I4I4I4I4I4", msg, i)}

    -- Extend the sixteen 32-bit words into sixty-four 32-bit words:
    for j = 17, 64 do
        local v = w[j - 15]
        local s0 = rrotate(v, 7) ~ rrotate(v, 18) ~ (v >> 3)       -- (1)
        v = w[j - 2]
        local s1 = rrotate(v, 17) ~ rrotate(v, 19) ~ (v >> 10)     -- (1)
        w[j] = (w[j - 16] + s0 + w[j - 7] + s1) & 0xffffffff       -- (2)
    end

    -- Initialize hash value for this chunk:
    local a, b, c, d, e, f, g, h =
        H[1], H[2], H[3], H[4], H[5], H[6], H[7], H[8]

    -- Main loop:
    for i = 1, 64 do
        local s0 = rrotate(a, 2) ~ rrotate(a, 13) ~ rrotate(a, 22) -- (1)
        local maj = (a & b) ~ (a & c) ~ (b & c)
        local t2 = s0 + maj                                        -- (1)
        local s1 = rrotate(e, 6) ~ rrotate(e, 11) ~ rrotate(e, 25) -- (1)
        local ch = (e & f) ~ (~e & g)
        local t1 = h + s1 + ch + k[i] + w[i]                       -- (1)

        h = g
        g = f
        f = e
        e = (d + t1) & 0xffffffff                                  -- (2)
        d = c
        c = b
        b = a
        a = (t1 + t2) & 0xffffffff                                 -- (2)
    end

    -- Add (mod 2^32) this chunk's hash to result so far:
    H[1] = (H[1] + a) & 0xffffffff
    H[2] = (H[2] + b) & 0xffffffff
    H[3] = (H[3] + c) & 0xffffffff
    H[4] = (H[4] + d) & 0xffffffff
    H[5] = (H[5] + e) & 0xffffffff
    H[6] = (H[6] + f) & 0xffffffff
    H[7] = (H[7] + g) & 0xffffffff
    H[8] = (H[8] + h) & 0xffffffff
end

local function finalresult224(H)
    -- Produce the final hash value (big-endian):
    return str2hexa(
        string.pack("> I4 I4 I4 I4 I4 I4 I4", H[1], H[2], H[3], H[4], H[5], H[6], H[7])
    )
end

local function finalresult256(H)
  -- Produce the final hash value (big-endian):
    return str2hexa(
        string.pack("> I4 I4 I4 I4 I4 I4 I4 I4", H[1], H[2], H[3], H[4], H[5], H[6], H[7], H[8])
    )
end

----------------------------------------------------------------------
local HH = {} -- to reuse

local function hash224(msg)
    msg = preproc(msg, #msg)
    local H = initH224(HH)

    -- Process the message in successive 512-bit (64 bytes) chunks:
    for i = 1, #msg, 64 do
        digestblock(msg, i, H)
    end

    return finalresult224(H)
end

local function hash256(msg)
    msg = preproc(msg, #msg)
    local H = initH256(HH)

    -- Process the message in successive 512-bit (64 bytes) chunks:
    for i = 1, #msg, 64 do
        digestblock(msg, i, H)
    end

    return finalresult256(H)
end

----------------------------------------------------------------------
local mt = {}

local function new256()
    local o = {H = initH256({}), msg = "", len = 0}
    setmetatable(o, mt)
    return o
end

mt.__index = mt

function mt:add(m)
    self.msg = self.msg .. m
    self.len = self.len + #m
    local t = 0
    while #self.msg - t >= 64 do
        digestblock(self.msg, t + 1, self.H)
        t = t + 64
    end
    self.msg = self.msg:sub(t + 1, -1)
end


function mt:close()
    self.msg = preproc(self.msg, self.len)
    self:add("")
    return finalresult256(self.H)
end

----------------------------------------------------------------------
-- Interface
return {
    hash224 = hash224,
    hash256 = hash256,
    new256 = new256,
}

end

local sha2 = require('sha2')

----------------------------------------------------------------------
-- tests for SHA-2 in Lua 5.3

sha2_test = function()

    local sha2 = require('sha2')

    -- a few examples from the Web

    assert(sha2.hash224"The quick brown fox jumps over the lazy dog" ==
        "730e109bd7a8a32b1cb9d9a09aa2325d2430587ddbc0c38bad911525")

    assert(sha2.hash224"" ==
        "d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f")

    assert(sha2.hash256"The quick brown fox jumps over the lazy dog" ==
        "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592")

    assert(sha2.hash256"The quick brown fox jumps over the lazy cog" ==
        "e4c4d8f3bf76b692de791a173e05321150f7a345b46484fe427f6acc7ecc81be")

    assert(sha2.hash256"" ==
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855")

    assert(sha2.new256():close() ==
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855")

    assert(sha2.hash256"123456" ==
        "8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92")

    -- most other examples here are checked against a "correct" answer
    -- given by 'sha224sum'/'sha256sum'

    -- border cases (sizes around 64 bytes)

    local t = { -- from 50 0's to 70 0's
        [50] = "9660acb8046abf46cf27280e61abd174ebac98ad6855e093772b78df85523129",
        [51] = "31e1c552b357ace9bcb924691799a3c0d3aa10d8b428d9de28a278e3c79ecb7b",
        [52] = "0be5c4bcb6f47e30c13515594dbef4faa3a6485af67c177179fee8b33cd4f2a0",
        [53] = "d368c7f6038c1743bdbfe6a9c3a72d4e6916aa219ed8d559766c9e8f9845f3b8",
        [54] = "7080a4aa6ff030ae152fe610a62ee29464f92afeb176474551a69d35aab154a0",
        [55] = "149c1cda81fa9359c0c2a5e405ca972986f1d53e05f6282871dd1581046b3f44",
        [56] = "eb2d4d41948ce546c8adff07ee97342070c5b89789f616a33efe52c7d3ec73d4",
        [57] = "c831db596ccbbf248023461b1c05d3ae084bcc79bcb2626c5ec179fb34371f2a",
        [58] = "1345b8a930737b1069bbf9b891ce095850f6cdba6e25874ea526a2ccb611fe46",
        [59] = "380ad21e466885fae080ceeada75ac04944687e626e161c0b24e91af3eec2def",
        [60] = "b9ab06fa30ef8531c5eee11651aa86f8279a245e0a3c29bf6228c59475cc610a",
        [61] = "bcc187de6605d9e11a0cc6edf02b67fb651fe1779ec59438788093d8e376c07c",
        [62] = "ae0b3681157b83b34de8591d2453915e40c3105ae79434e241d82d4035218e01",
        [63] = "68a27b4735f6806fb5983c1805a23797aa93ea06e0ebcb6daada2ea1ab5a05af",
        [64] = "827d096d92f3deeaa0e8070d79f45beb176768e57a958a1cd325f5f4b754b048",
        [65] = "6c7bd8ec0fe9b4e05a2d27dd5e41a8687a9716a2e8926bdfa141266b12942ec1",
        [66] = "2f4b4c41017a2ddd1cc8cd75478a82e9452e445d4242f09782535376d6f4ba50",
        [67] = "b777b86e005807a446ead00986fcbf3bdd6c022524deabf017eeb3f0c30b6eed",
        [68] = "777da331f60c793f582e4ca33223778218ddfd241981f15be5886171fb8301b5",
        [69] = "06ed0c4cbf7d2b38de5f01eab2d2cd552d9cb87f97b714b96bb7a9d1b6117c6d",
        [70] = "e82223344d5f3c024514cfbe6d478b5df98bb878f34d7a07e7b064fa7fa91946"
    }

    for i = 50, 70 do
        assert(sha2.hash256(string.rep('0', i) .. '\n') == t[i])
    end

    local x = sha2.new256()
    for i = 1, 65 do x:add('a') end
    x:add('\n')
    assert(x:close() ==
        "574883a9977284a46845620eaa55c3fa8209eaa3ebffe44774b6eb2dba2cb325")

    -- some large files
    local function parts (s, j)
        local x = sha2.new256()
        local i = 1
        while i <= #s do
            x:add(s:sub(i, i + j))
            i = i + j + 1
        end
        return x:close()
    end

    -- 80 lines of 80 '0's each
    local s = string.rep('0', 80) .. '\n'
    s = string.rep(s, 80)
    assert(parts(s, 70) ==
        "736c7a8b17e2cfd44a3267a844db1a8a3e8988d739e3e95b8dd32678fb599139")
    assert(parts(s, 7) ==
        "736c7a8b17e2cfd44a3267a844db1a8a3e8988d739e3e95b8dd32678fb599139")
    assert(parts(s, #s + 10) ==
        "736c7a8b17e2cfd44a3267a844db1a8a3e8988d739e3e95b8dd32678fb599139")

    -- read a file and prints its hash, if given a file name

    if arg[1] then
        local file = assert(io.open (arg[1], 'rb'))
        local x = sha2.new256()
        for b in file:lines(2^12) do
            x:add(b)
        end
        file:close()
        print(x:close())
    end
end
