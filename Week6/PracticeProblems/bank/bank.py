greeting_values = {
    "Hello": 0,
    "Hello, newman": 0,
    "How you doing?": 20,
    "What's happening?": 100,
    "What's up?": 100,

}
greeting = input("Greeting: ")
output = 0
if greeting in greeting_values:
    output = greeting_values[greeting]

print(f"${output}")
