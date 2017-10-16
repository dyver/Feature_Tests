#!/usr/bin/env lua

package.path = './cgi-bin/?.lua;' .. package.path

local cgi = require 'cgi'
local lfs = require 'lfs'
local sha2 = require 'sha2'
local pm = require 'pm'

local temporary_directory = (os.getenv('TEMP') or '/tmp') .. '/'
local program_work_directory = temporary_directory .. 'backuper_archiver/'

local parameters = cgi.parameters().Post
parameters.ClientAddress = cgi.parameters().REMOTE_ADDR
parameters.Action = parameters.Action or 'prompt'
parameters.Login = parameters.Login or 'Nobody'
local security_hash_file = program_work_directory .. parameters.ClientAddress:gsub('[:.]', '_')

local session_key = 0
local session_key_file = security_hash_file
local login_work_directory = program_work_directory .. parameters.Login .. '/'

local user_configuration = {}
local status
local packer_pid_file = login_work_directory .. 'pid'
local packer_command_file = login_work_directory .. 'packer.lua'
local packer_destination_directory

local create_security_hash = function()
    local security_hash = sha2.hash256(parameters.ClientAddress .. math.random(1, 10000))
    lfs.mkdir(program_work_directory)
    local f = assert(io.open(security_hash_file, 'w'))
    f:write(security_hash)
    f:close()
    parameters.SecurityHash = security_hash
end

local read_security_hash = function()
    local f = assert(io.open(security_hash_file, 'r'))
    local result = f:read('a')
    f:close()
    parameters.SecurityHash = result
end

local check_login = function(fake)
    local login = parameters.Login
    local client_key_hash = parameters.SessionKeyHash
    local security_hash = parameters.SecurityHash or ''
    local logins_file = './auth/logins.conf'
    local result, name
    local Login = function(records)
        for key, value in pairs(records) do
            if key == login then
                local server_key_hash = sha2.hash256(value.password .. security_hash)
                if client_key_hash == server_key_hash or fake then
                    result = true
                else
                    result = false
                end
                name = value.name or login
                return
            end
        end
        name = login
    end
    local f = loadfile(logins_file)
    debug.setupvalue(f, 1, { Login = Login })
    f()
    return result, name
end

local create_session_key = function()
    local key = parameters.SessionKeyHash
    lfs.mkdir(program_work_directory)
    local f = io.open(session_key_file, 'w')
    f:write(key)
    f:close()
end

local check_session = function()
    local f = io.open(session_key_file, 'r')
    if not f then
        return false
    end
    local result = f:read('a')
    f:close()
    if result == parameters.SessionKeyHash then
        return true
    end
    return false
end

local report_login_result = function(result, name)
    if result == true then
        append_to_page('<h1 align="center">Добро пожаловать, <em>' .. name .. '</em>.</h1>')
    elseif result == false then
        append_to_page('<h1>Уважаемый <em>' .. name .. '</em>, вы ввели неверный пароль.')
    else
        append_to_page('<h1>Неизвестная учётная запись: <em>' .. name .. '</em>.</h1>')
    end
end

local read_user_configuration = function()
    local login = parameters.Login
    local directories_list_file = './data/' .. login .. '.conf'
    local result
    local Configuration = function(records)
        for _, value in ipairs(records) do
            if lfs.attributes(value, 'mode') ~= 'directory' then
                value = value .. '  <em>&larr; такого каталога нет</em>'
            end
            table.insert(user_configuration, value)
        end
        if type(records.destination) == 'table' then
            for _, value in ipairs(records.destination) do
                if lfs.attributes(value, 'mode') == 'directory' then
                    packer_destination_directory = value .. '/' .. login
                    break
                end
            end
        else
            packer_destination_directory = (records.destination or '/tmp/') .. login
        end
    end
    local load_configuration, error_message = loadfile(directories_list_file)
    if load_configuration then
        debug.setupvalue(load_configuration, 1, { Configuration = Configuration })
        load_configuration()
    else
        report_error(error_message)
    end
    lfs.mkdir(packer_destination_directory)
    if lfs.attributes(packer_destination_directory, 'mode') == nil then
        report_error('No such directory: ' .. packer_destination_directory)
        user_configuration = {}
        return
    end
end

local show_user_configuration = function()
    if #user_configuration == 0 then return end
    append_to_page('<h3>Это ваш список архивируемых каталогов:</h3>')
    local list = {}
    table.insert(list, '<ul type="square">')
    for _, item in ipairs(user_configuration) do
        table.insert(list, '<li>' .. item .. '</li>')
    end
    table.insert(list, '</ul>')
    append_to_page(table.concat(list))
    append_to_page('<h3>Архивы будут созданы в следующем каталоге:</h3>')
    append_to_page(packer_destination_directory)
    append_to_page('<hr size=5 noshade>')
end

local start_process = function()
    lfs.mkdir(login_work_directory)
    lfs.mkdir(packer_destination_directory)
    local f = assert(io.open(packer_command_file, 'w'))
    for i, directory_to_pack in ipairs(user_configuration) do
        if lfs.attributes(directory_to_pack, 'mode') == 'directory' then
            local pack_file = packer_destination_directory .. '/' .. i .. '_pack.7z'
            os.remove(pack_file)
            pack_command = {
                '7z',
                'a',
                '-t7z',  -- 7z archive
                '-m0=lzma',  -- lzma method
                '-mfb=64',  -- 64 fast bytes for LZMA
                '-md=32m',  -- dictionary size = 32 megabytes
                '-mx=9',  -- ultra compression
                '-ms=on',  -- solid archive
                pack_file,
                '"' .. directory_to_pack .. '"',
            }
            pack_command = table.concat(pack_command, ' ')
            pack_command = pack_command:gsub('\\', '/')
            f:write('os.execute(\'' .. pack_command .. '\')\n')
        end
    end
    f:close()
    if lfs.attributes(packer_command_file, 'size') ~= 0 then
        local pid = pm.start_process('lua ' .. packer_command_file)
        f = assert(io.open(packer_pid_file, 'w'))
        f:write(pid)
        f:close()
    end
end

local add_login_form = function()
    append_to_page('<h1>Вас приветствует программа создания резервной копии.</h1>')
    append_to_page('<h2>Введите имя учётной записи и пароль:</h2>')
    local form = [[
        <script src='/js/sha256.js'></script>
        <script src='/js/onSubmit.js'></script>
        <form action='/cgi-bin/main.lua' method='post' onsubmit='return onSubmit();'>
            <input type='hidden' name='Action' value='login' maxlength='15'/>
            <input type='hidden' name='SessionKeyHash' maxlength='100'/>
            <input type='hidden' name='SecurityHash'
                value=']] .. parameters.SecurityHash .. [[' maxlength='100'
            />
            <table>
                <tbody>
                    <tr>
                        <td>Учётная запись</td>
                        <td><input type='text' name='Login' size='20' maxlength='15'/></td>
                    </tr>
                    <tr>
                        <td>Пароль</td>
                        <td><input type='password' name='Password' size='20' maxlength='15'/></td>
                    </tr>
                    <tr>
                        <td><input type='submit' value='Ввод'/></td>
                    </tr>
                </tbody>
            </table>
        </form>
    ]]
    append_to_page(form)
end

local add_start_form = function()
    local form_head = [[
        <form action='/cgi-bin/main.lua' method='post'>
            <div><input type='hidden' name='Login' value=']] .. parameters.Login .. [[' /></div>
            <div>
                <input type='hidden' name='SessionKeyHash'
                    value=']] .. parameters.SessionKeyHash .. [['
                />
            </div>
            <table>
                <tbody>
                    <tr>
    ]]
    local form_tail = [[
                    </tr>
                </tbody>
            </table>
        </form>
    ]]
    append_to_page(form_head)
    if #user_configuration == 0 then return end
    if (not status) then
        append_to_page([[
            <td>
                <input type='submit' value='Начать резервное копирование' />
            </td>
            <div><input type='hidden' name='Action' value='start' /></div>
        ]])
    else
        append_to_page([[
            <td>
                <input type='submit' value='Обновить статус' />
            </td>
            <div><input type='hidden' name='Action' value='status' /></div>
        ]])
    end
end

local add_status_form = function()
    local retreive_pid = function()
        local f = io.open(packer_pid_file, 'r')
        if not f then
            return 0
        end
        local result = f:read('a')
        f:close()
        return result
    end
    local check_process_started = function()
        return pm.is_process_exist(retreive_pid())
    end
    if #user_configuration == 0 then return end
    if not check_process_started() then
        append_to_page('<h3>Система готова начать резервное копирование</h3>')
        status = false
    else
        append_to_page('<h3>Идёт резервное копирование</h3>')
        status = true
    end
end

local actions = {}

actions.prompt = function()
    create_security_hash()
    add_login_form()
end

actions.login = function()
    read_security_hash()
    local result, name = check_login()
    report_login_result(result, name)
    if not result then
        return
    end
    create_session_key()
    read_user_configuration()
    show_user_configuration()

    add_status_form()
    add_start_form()
end

actions.start = function()
    if not check_session() then
        actions.prompt()
        return
    end
    local result, name = check_login(true)
    report_login_result(result, name)
    read_user_configuration()
    show_user_configuration()
    start_process()
    add_status_form()
    add_start_form()
end

actions.status = function()
    if not check_session() then
        actions.prompt()
        return
    end
    local result, name = check_login(true)
    report_login_result(result, name)
    read_user_configuration()
    show_user_configuration()
    add_status_form()
    add_start_form()
end

actions[parameters.Action]()
