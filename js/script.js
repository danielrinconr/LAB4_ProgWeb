function LogIn()
{
    $.get('/LogIn',
    {
        username: $(username).value,
        password: $(username).value
    });
}

// $("button").click(function(){
//     $.post("demo_test_post.asp",
//     {
//       name: "Donald Duck",
//       city: "Duckburg"
//     });
// });