# php_signature
一些场景中的加密,秘钥在头文件中定义,防止泄露

## 使用方法
秘钥在php_signature.h头文件中定义
方法：
- signature_in($str, $suffix=false) : string  $str 源字符串,$suffix秘钥是否在字符串后缀
- signature_verify($str, $signed, $suffix) : bool  $str 源字符串, $signed 加密后字符串 $suffix 秘钥是否后缀

```
$str = 12; 
$signed_str = signature_in($str);
echo $signed_str."\n";
var_dump(signature_verify($str, $signed_str));
var_dump(signature_verify($str, $signed_str."test"));

$signed_str = signature_in($str, true);
echo $signed_str."\n";
var_dump(signature_verify($str, $signed_str, true));
var_dump(signature_verify($str, $signed_str."test", true));

```
输出结果：

```
// 前缀模式
ceebb27eaaafbd3b866484f9b39e2cddaefc8687
bool(true)
bool(false)

// 后缀模式
51ad16c8f206ff2b2d40f5648b8a55a10dd7c1dd
bool(true)
bool(false)

```
