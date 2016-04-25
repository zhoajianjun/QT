function qbsVersion() { return "1.4.3"; }

function versionIsAtLeast(actualVersion, expectedVersion)
{
    var actualVersionParts = actualVersion.split('.').map(function(item) {
        return parseInt(item, 10);
    });
    var expectedVersionParts = expectedVersion.split('.').map(function(item) {
        return parseInt(item, 10);
    });
    for (var i = 0; i < expectedVersionParts.length; ++i) {
        if (actualVersionParts[i] > expectedVersionParts[i])
            return true;
        if (actualVersionParts[i] < expectedVersionParts[i])
            return false;
    }
    return i === expectedVersionParts.length || expectedVersionParts[i] === 0;
}
