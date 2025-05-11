# dayz-mod-carim

https://steamcommunity.com/sharedfiles/filedetails/?id=3468061029

## Getting color values from hex
For the `cfggameplay.json` color values, they need to be integers. Those
values can be determined from the hex string by getting the signed integer
as follows (Python example):

```python
def convert(value: str) -> int:
    as_bytes = bytes.fromhex(value)
    return int.from_bytes(as_bytes, byteorder='big', signed=True)

# hex string as ARGB bytes
value = "fffafafa"
print(convert(value))
```
