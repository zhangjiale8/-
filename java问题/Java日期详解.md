## 背景

在 Java 8 之前，我们最常见的时间与日期处理相关的类就是 Date、Calendar 以及 SimpleDateFormatter 等等。不过 `java.util.Date` 也是被诟病已久，它包含了日期、时间、毫秒数等众多繁杂的信息，其内部利用午夜 12 点来区分日期，利用 1970-01-01 来计算时间；并且其月份从 0 开始计数，而且用于获得年、月、日等信息的接口也是太不直观。除此之外，`java.util.Date` 与 `SimpleDateFormatter` 都不是类型安全的，而 JSR-310 中的 `LocalDate` 与 `LocalTime` 等则是不变类型，更加适合于并发编程。JSR 310 实际上有两个日期概念。第一个是 Instant，它大致对应于 `java.util.Date` 类，因为它代表了一个确定的时间点，即相对于标准 Java 纪元（1970年1月1日）的偏移量；但与 `java.util.Date` 类不同的是其精确到了纳秒级别。另一个则是 LocalDate、LocalTime 以及 LocalDateTime 这样代表了一般时区概念、易于理解的对象。

Java8中, `java.time`包下包含下面几个主要的类:

```
Instant：时间戳
Duration：持续时间，时间差
LocalDate：只包含日期，比如：2016-10-20
LocalTime：只包含时间，比如：23:12:10
LocalDateTime：包含日期和时间，比如：2016-10-20 23:14:21
Period：时间段
ZoneOffset：时区偏移量，比如：+8:00
ZonedDateTime：带时区的时间
Clock：时钟，比如获取目前美国纽约的时间
```



| Class / Type  | Description                                                  |
| :------------ | :----------------------------------------------------------- |
| Year          | Represents a year.                                           |
| YearMonth     | A month within a specific year.                              |
| LocalDate     | A date without an explicitly specified time zone.            |
| LocalTime     | A time without an explicitly specified time zone.            |
| LocalDateTime | A combination date and time without an explicitly specified time zone. |

最新 JDBC 映射将把数据库的日期类型和 Java 8 的新类型关联起来：

| SQL       | Java          |
| :-------- | :------------ |
| date      | LocalDate     |
| time      | LocalTime     |
| timestamp | LocalDateTime |
| datetime  | LocalDateTime |

## 时间与日期基础概念

### 标准时间

GMT 即「格林威治标准时间」( Greenwich Mean Time，简称 G.M.T. )，指位于英国伦敦郊区的皇家格林威治天文台的标准时间，因为本初子午线被定义为通过那里的经线。然而由于地球的不规则自转，导致 GMT 时间有误差，因此目前已不被当作标准时间使用。UTC 是最主要的世界时间标准，是经过平均太阳时(以格林威治时间 GMT 为准)、地轴运动修正后的新时标以及以「秒」为单位的国际原子时所综合精算而成的时间。UTC 比 GMT 来得更加精准。其误差值必须保持在 0.9 秒以内，若大于 0.9 秒则由位于巴黎的国际地球自转事务中央局发布闰秒，使 UTC 与地球自转周期一致。不过日常使用中，GMT 与 UTC 的功能与精确度是没有差别的。协调世界时区会使用 “Z” 来表示。而在航空上，所有使用的时间划一规定是协调世界时。而且 Z 在无线电中应读作 “Zulu”（可参见北约音标字母），协调世界时也会被称为 “Zulu time”。

### TimeZone&UTC Offsets: 时区与偏移

人们经常会把时区与 UTC 偏移量搞混，UTC 偏移量代表了某个具体的时间值与 UTC 时间之间的差异，通常用 HH:mm 形式表述。而 TimeZone 则表示某个地理区域，某个 TimeZone 中往往会包含多个偏移量，而多个时区可能在一年的某些时间有相同的偏移量。譬如 America/Chicago, America/Denver, 以及 America/Belize 在一年中不同的时间都会包含 -06:00 这个偏移。

### 时间戳

Unix 时间戳表示当前时间到 1970 年 1 月 1 日 00:00:00 UTC 对应的秒数。注意，JavaScript 内的时间戳指的是当前时间到 1970 年 1 月 1 日 00:00:00 UTC 对应的毫秒数，和 Unix 时间戳不是一个概念，后者表示秒数，差了 1000 倍。

## 时间数字字符串格式

### RFC2822

```
YYYY/MM/DD HH:MM:SS ± timezone(时区用4位数字表示)
// eg 1992/02/12 12:23:22+0800
```

### ISO 8601

国际标准化组织的国际标准 ISO 8601 是日期和时间的表示方法，全称为《数据存储和交换形式·信息交换·日期和时间的表示方法》。目前最新为第三版 ISO8601:2004，第一版为 ISO8601:1988，第二版为 ISO8601:2000。年由 4 位数组成，以公历公元 1 年为 0001 年，以公元前 1 年为 0000 年，公元前 2 年为 -0001 年，其他以此类推。应用其他纪年法要换算成公历，但如果发送和接受信息的双方有共同一致同意的其他纪年法，可以自行应用。

```
YYYY-MM-DDThh:mm:ss ± timezone(时区用HH:MM表示)
1997-07-16T08:20:30Z
// “Z”表示UTC标准时区，即"00:00",所以这里表示零时区的`1997年7月16日08时20分30秒`
//转换成位于东八区的北京时间则为`1997年7月17日16时20分30秒
1997-07-16T19:20:30+01:00
// 表示东一区的1997年7月16日19时20秒30分，转换成UTC标准时间的话是1997-07-16T18:20:30Z
```

## 时间戳

在 Java 8 之前，我们使用 `java.sql.Timestamp` 来表示时间戳对象，可以通过以下方式创建与获取对象：

```
// 利用系统标准时间创建
Timestamp timestamp = new Timestamp(System.currentTimeMillis());

// 从 Date 对象中创建
new Timestamp((new Date()).getTime());

// 获取自 1970-01-01 00:00:00 GMT 以来的毫秒数
timestamp.getTime();
```

在 Java 8 中，即可以使用 `java.time.Instant` 来表示自从 1970-01-01T00:00:00Z 之后经过的标准时间：

```
// 基于静态函数创建
Instant instant = Instant.now();

// 基于 Date 或者毫秒数转换
Instant someInstant = someDate.toInstant();
Instant someInstant = Instant.ofEpochMilli(someDate.getTime());

// 基于 TimeStamp 转换
Instant instant = timestamp.toInstant();

// 从 LocalDate 转化而来
LocalDate.now().atStartOfDay().toInstant(ZoneOffset.UTC)

// 从 LocalDateTime 转化而来
ldt.atZone(ZoneId.systemDefault()).toInstant();

// 获取毫秒
long timeStampMillis = instant.toEpochMilli();

// 获取秒
long timeStampSeconds = instant.getEpochSecond();
```

Clock 方便我们去读取当前的日期与时间。Clock 可以根据不同的时区来进行创建，并且可以作为`System.currentTimeMillis()`的替代。这种指向时间轴的对象即是`Instant`类。Instants 可以被用于创建`java.util.Date`对象。

```
Clock clock = Clock.systemDefaultZone();
long millis = clock.millis();

Instant instant = clock.instant();
Date legacyDate = Date.from(instant);   // legacy java.util.Date
```

## Date

```
// 默认创建
Date date0 = new Date();

// 从 TimeStamp 中创建
Date date1 = new Date(time);

// 基于 Instant 创建
Date date = Date.from(instant);

// 从格式化字符串中获取
SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd");
java.util.Date dt=sdf.parse("2005-2-19");

// 从 LocalDateTime 中转化而来
Date out = Date.from(ldt.atZone(ZoneId.systemDefault()).toInstant());
```

基于 Date 的日期比较常常使用以下方式：

- 使用 getTime() 方法获取两个日期（自1970年1月1日经历的毫秒数值），然后比较这两个值。
- 使用方法 before()，after() 和 equals()。例如，一个月的12号比18号早，则 `new Date(99, 2, 12).before(new Date (99, 2, 18))` 返回true。
- 使用 `compareTo()` 方法，它是由 Comparable 接口定义的，Date 类实现了这个接口。

### Calendar

Date 用于记录某一个含日期的、精确到毫秒的时间。重点在代表一刹那的时间本身。 Calendar 用于将某一日期放到历法中的互动——时间和年、月、日、星期、上午、下午、夏令时等这些历法规定互相作用关系和互动。我们可以通过 Calendar 内置的构造器来创建实例：

```
Calendar.Builder builder =new Calendar.Builder();
Calendar calendar1 = builder.build();
Date date = calendar.getTime();
```

在 Calendar 中我们则能够获得较为直观的年月日信息：

```
// 2017，不再是 2017 - 1900 = 117
int year =calendar.get(Calendar.YEAR);

int month=calendar.get(Calendar.MONTH)+1;

int day =calendar.get(Calendar.DAY_OF_MONTH);

int hour =calendar.get(Calendar.HOUR_OF_DAY);

int minute =calendar.get(Calendar.MINUTE);

int seconds =calendar.get(Calendar.SECOND);
```

除此之外，Calendar 还提供了一系列 set 方法来允许我们动态设置时间，还可以使用 add 等方法进行日期的加减。

## LocalDateTime

### LocalDate

```
// 取当前日期：
LocalDate today = LocalDate.now();

// 根据年月日取日期，12月就是12：
LocalDate crischristmas = LocalDate.of(2017, 5, 15); 

// 根据指定格式字符串取
LocalDate endOfFeb = LocalDate.parse("2017-05-15"); // 严格按照ISO yyyy-MM-dd验证，02写成2都不行，当然也有一个重载方法允许自己定义格式
LocalDate.parse("2014-02-29"); // 无效日期无法通过：DateTimeParseException: Invalid date

// 通过自定义时间字符串格式获取
DateTimeFormatter germanFormatter =
      DateTimeFormatter
            .ofLocalizedDate(FormatStyle.MEDIUM)
            .withLocale(Locale.GERMAN);

LocalDate xmas = LocalDate.parse("24.12.2014", germanFormatter);
System.out.println(xmas);   // 2014-12-24

// 获取其他时区下日期
LocalDate localDate = LocalDate.now(ZoneId.of("GMT+02:30"));

// 从 LocalDateTime 中获取实例
LocalDateTime localDateTime = LocalDateTime.now();
LocalDate localDate = localDateTime.toLocalDate();
```

### 日期操作

```
// 取本月第1天
LocalDate firstDayOfThisMonth = today.with(TemporalAdjusters.firstDayOfMonth()); // 2014-12-01

// 取本月第2天
LocalDate secondDayOfThisMonth = today.withDayOfMonth(2); // 2014-12-02

// 取本月最后一天，再也不用计算是28，29，30还是31
LocalDate lastDayOfThisMonth = today.with(TemporalAdjusters.lastDayOfMonth()); // 2014-12-31

// 取下一天
LocalDate firstDayOf2015 = lastDayOfThisMonth.plusDays(1); // 变成了2015-01-01

// 取2015年1月第一个周一
LocalDate firstMondayOf2015 = LocalDate.parse("2015-01-01").with(TemporalAdjusters.firstInMonth(DayOfWeek.MONDAY)); // 2015-01-05
```

## LocalTime

```
// 获取其他时区下时间
LocalTime localTime = LocalTime.now(ZoneId.of("GMT+02:30"));

// 从 LocalDateTime 中获取实例
LocalDateTime localDateTime = LocalDateTime.now();
LocalTime localTime = localDateTime.toLocalTime();

- 12:00
- 12:01:02
- 12:01:02.345
```

## LocalDateTime

```
// 通过时间戳创建
LocalDateTime localDateTime = LocalDateTime.ofInstant(Instant.ofEpochSecond(1450073569l), TimeZone.getDefault().toZoneId());

// 通过 Date 对象创建
Date in = new Date();
LocalDateTime ldt = LocalDateTime.ofInstant(in.toInstant(), ZoneId.systemDefault());

// 通过解析时间字符串创建
DateTimeFormatter formatter =
    DateTimeFormatter
      .ofPattern("MMM dd, yyyy - HH:mm");

LocalDateTime parsed = LocalDateTime.parse("Nov 03, 2014 - 07:13", formatter);
String string = formatter.format(parsed);
System.out.println(string);     // Nov 03, 2014 - 07:13
```

- 获取年、月、日等信息

```
LocalDateTime sylvester = LocalDateTime.of(2014, Month.DECEMBER, 31, 23, 59, 59);

DayOfWeek dayOfWeek = sylvester.getDayOfWeek();
System.out.println(dayOfWeek);  // WEDNESDAY

Month month = sylvester.getMonth();
System.out.println(month);  // DECEMBER

long minuteOfDay = sylvester.getLong(ChronoField.MINUTE_OF_DAY);
System.out.println(minuteOfDay);  // 1439
```

- 时间格式化展示

```
DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
LocalDateTime dateTime = LocalDateTime.of(1986, Month.APRIL, 8, 12, 30);
String formattedDateTime = dateTime.format(formatter); // "1986-04-08 12:30"
```

### 时间操作

```
localDateTime.plusDays(1);
localDateTime.minusHours(2);
```

## 时区转换

Timezones 以 `ZoneId` 来区分。可以通过静态构造方法很容易的创建，Timezones 定义了 Instants 与 Local Dates 之间的转化关系：

```
System.out.println(ZoneId.getAvailableZoneIds());
// prints all available timezone ids

ZoneId zone1 = ZoneId.of("Europe/Berlin");
ZoneId zone2 = ZoneId.of("Brazil/East");
System.out.println(zone1.getRules());
System.out.println(zone2.getRules());

// ZoneRules[currentStandardOffset=+01:00]
// ZoneRules[currentStandardOffset=-03:00]
LocalDateTime ldt = ...
ZonedDateTime zdt = ldt.atZone(ZoneId.systemDefault());
Date output = Date.from(zdt.toInstant());
ZoneId losAngeles = ZoneId.of("America/Los_Angeles");
ZoneId berlin = ZoneId.of("Europe/Berlin");

// 2014-02-20 12:00
LocalDateTime dateTime = LocalDateTime.of(2014, 02, 20, 12, 0);

// 2014-02-20 12:00, Europe/Berlin (+01:00)
ZonedDateTime berlinDateTime = ZonedDateTime.of(dateTime, berlin);

// 2014-02-20 03:00, America/Los_Angeles (-08:00)
ZonedDateTime losAngelesDateTime = berlinDateTime.withZoneSameInstant(losAngeles);

int offsetInSeconds = losAngelesDateTime.getOffset().getTotalSeconds(); // -28800

// a collection of all available zones
Set<String> allZoneIds = ZoneId.getAvailableZoneIds();

// using offsets
LocalDateTime date = LocalDateTime.of(2013, Month.JULY, 20, 3, 30);
ZoneOffset offset = ZoneOffset.of("+05:00");

// 2013-07-20 03:30 +05:00
OffsetDateTime plusFive = OffsetDateTime.of(date, offset);

// 2013-07-19 20:30 -02:00
OffsetDateTime minusTwo = plusFive.withOffsetSameInstant(ZoneOffset.ofHours(-2));
```

## 时差

Period 类以年月日来表示日期差，而 Duration 以秒与毫秒来表示时间差；Duration 适用于处理 Instant 与机器时间。

```
// periods

LocalDate firstDate = LocalDate.of(2010, 5, 17); // 2010-05-17
LocalDate secondDate = LocalDate.of(2015, 3, 7); // 2015-03-07
Period period = Period.between(firstDate, secondDate);

int days = period.getDays(); // 18
int months = period.getMonths(); // 9
int years = period.getYears(); // 4
boolean isNegative = period.isNegative(); // false

Period twoMonthsAndFiveDays = Period.ofMonths(2).plusDays(5);
LocalDate sixthOfJanuary = LocalDate.of(2014, 1, 6);

// add two months and five days to 2014-01-06, result is 2014-03-11
LocalDate eleventhOfMarch = sixthOfJanuary.plus(twoMonthsAndFiveDays);

// durations

Instant firstInstant= Instant.ofEpochSecond( 1294881180 ); // 2011-01-13 01:13
Instant secondInstant = Instant.ofEpochSecond(1294708260); // 2011-01-11 01:11

Duration between = Duration.between(firstInstant, secondInstant);

// negative because firstInstant is after secondInstant (-172920)
long seconds = between.getSeconds();

// get absolute result in minutes (2882)
long absoluteResult = between.abs().toMinutes();

// two hours in seconds (7200)
long twoHoursInSeconds = Duration.ofHours(2).getSeconds();
```

## Date和LocalDateTime转换

### Date转LocalDateTime

```
// 2000-2-10 11:10:10
Date d = new Date(950152210000L)
LocalDateTime ldt = LocalDateTime.ofInstant(d.toInstant, ZoneId.of("America/New_York"))
```

### LocalDateTime转Date

```
LocalDateTime ldt = LocalDateTime.now()
Date d = Date.from(ldt.atZone(ZoneId.of("Asia/Shanghai")).toInstant)
```

### Date转ZonedDateTime

```
// 2000-2-10 11:10:10
Date d = new Date(950152210000L)
ZonedDateTime zdt = ZonedDateTime.ofInstant(d.toInstant, ZoneId.of("America/New_York"))
```



http://www.arccode.net/java-date.html#more