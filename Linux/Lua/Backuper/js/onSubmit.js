function onSubmit() {
    var password = document.getElementsByName('Password')[0];
    var sessionKeyHash = document.getElementsByName('SessionKeyHash')[0];
    var securityHash = document.getElementsByName('SecurityHash')[0];
    sessionKeyHash.value = CryptoJS.SHA256(CryptoJS.SHA256(password.value) + securityHash.value);
    password.value = '';
    return true;
}
