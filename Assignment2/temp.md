```sequence
participant 本岸
participant 对岸

本岸 -> 对岸: a, b

note left of 本岸: 士兵
```

```sequence
participant 本岸
participant 对岸

对岸 -> 本岸: b

note right of 对岸: a
note left of 本岸: 士兵

```

```sequence
participant 本岸
participant 对岸

本岸 -> 对岸: 士兵

note left of 本岸: b
note right of 对岸: a
```

```sequence
participant 本岸
participant 对岸

对岸 -> 本岸: a

note left of 本岸: b
note right of 对岸: 士兵
```