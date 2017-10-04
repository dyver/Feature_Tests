local cgi = {}

-- Return a urlencoded copy of s. For example,
--   "Here & there + 97% of other places"
-- is encoded as
--   "Here%20%26%20there%20%2B%2097%25%20of%20other%20places"
cgi.encode = function(s)
    return (s:gsub('%W', function(c)
        return string.format('%%%02X', string.byte(c))
    end))
end

-- Returns a urldecoded copy of s. This function reverses the effects of cgi.encode.
cgi.decode = function(s)
    return (s:gsub('%+', ' '):gsub('%%(%x%x)', function(c) return string.char(tonumber(c, 16)) end))
end

-- Returns an escaped copy of s in which the characters &<>" are escaped for
-- display in HTML documents.
cgi.escape = function(s)
    return (s:gsub('%&', '&amp;'):gsub('%"', '&quot;'):gsub('%<', '&lt;'):gsub('%>', '&gt;'))
end

-- This function returns an associative array with the parsed contents of the
-- urlencoded string s. Multiple values with the same name are placed into an
-- indexed table with the name.
local local_parse = function(s)
    local decode, result = cgi.decode, {}
    for key_string, value_string in string.gmatch(s .. '&', '(.-)%=(.-)%&') do
        local key = decode(key_string)
        local value = decode(value_string)
        local item = result[key]
        local item_type = type(item)
        -- If there are multiple values with the same name, place them in an indexed table.
        if item_type == 'string' then -- replace string with table
            result[key] = { item, value }
        elseif item_type == 'table' then -- insert into existing table
            table.insert(item, value)
        else -- add as string field
            result[key] = value
        end
    end
    return result
end

-- Returns an associative array with both the GET and POST contents which
-- accompany an HTTP request. Multi-part form data, usually used with uploaded
-- files, is not currently supported.
local parameters_cache
cgi.parameters = function()
    if parameters_cache then return parameters_cache end
    parameters_cache = {}
    local keys = {
        'PATH_INFO',
        'PATH_TRANSLATED',
        'REMOTE_HOST',
        'REMOTE_ADDR',
        'GATEWAY_INTERFACE',
        'SCRIPT_NAME',
        'REQUEST_METHOD',
        'HTTP_ACCEPT',
        'HTTP_ACCEPT_CHARSET',
        'HTTP_ACCEPT_ENCODING',
        'HTTP_ACCEPT_LANGUAGE',
        'HTTP_FROM',
        'HTTP_HOST',
        'HTTP_REFERER',
        'HTTP_USER_AGENT',
        'QUERY_STRING',
        'SERVER_SOFTWARE',
        'SERVER_NAME',
        'SERVER_PROTOCOL',
        'SERVER_PORT',
        'CONTENT_TYPE',
        'CONTENT_LENGTH',
        'AUTH_TYPE'
    }

    for _, key in ipairs(keys) do
        parameters_cache[key] = os.getenv(key)
    end
    local post_string, post_string_length
    if not parameters_cache.SERVER_SOFTWARE then -- Command line invocation
        parameters_cache.QUERY_STRING = arg[1]
        post_string = arg[2]
    elseif 'application/x-www-form-urlencoded' == parameters_cache.CONTENT_TYPE then
        -- Web server invocation with posted urlencoded content
        post_string_length = tonumber(parameters_cache.CONTENT_LENGTH)
        if post_string_length and post_string_length > 0 then
            post_string = io.read(post_string_length)
        end
    end
    post_string = post_string or ''
    parameters_cache.Post = local_parse(post_string)
    parameters_cache.POST_STRING = post_string
    local get_string = parameters_cache.QUERY_STRING or ''
    parameters_cache.Get = local_parse(get_string)
    return parameters_cache
end

cgi.formatted_parameters = function()
    local result = {}
    local styles = [[
        <style>
            .first { margin: 0px; font-size: 12px; }
            .second { margin: 0px; margin-left: 30px; margin-bottom: 10px; font-size: 12px; }
        </style>
    ]]
    table.insert(result, styles)
    cgi.parameters()
    local keys = {}
    for key, _ in pairs(parameters_cache) do
        table.insert(keys, tostring(key))
    end
    table.sort(keys)
    for _, key_name in ipairs(keys) do
        local inner_value = parameters_cache[key_name]
        if type(inner_value) == 'table' then
            table.insert(result, '<p class="first">')
            table.insert(result, key_name .. ':')
            table.insert(result, '</p>')
            local inner_keys = {}
            for key, _ in pairs(inner_value) do
                table.insert(inner_keys, tostring(key))
            end
            table.sort(inner_keys)
            table.insert(result, '<p class="second">')
            local subvalue = {}
            for _, inner_key_name in ipairs(inner_keys) do
                table.insert(subvalue, cgi.escape(inner_key_name) .. '='
                    .. cgi.escape(tostring(inner_value[inner_key_name])) .. '<br>')
            end
            table.sort(subvalue)
            table.move(subvalue, 1, #subvalue, #result + 1, result)
            table.insert(result, '</p>')
        else
            table.insert(result, '<p class="first">')
            table.insert(result, cgi.escape(key_name) .. '='
                .. cgi.escape(tostring(parameters_cache[key_name])) .. '<br>')
            table.insert(result, '</p>')
        end
    end
    return table.concat(result, '\n')
end

return cgi
