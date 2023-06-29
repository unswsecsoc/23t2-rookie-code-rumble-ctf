# Reinterpret

## Authors

- @ssparrow

## Category

- Web

## Description

The aliens have tried implementing their new API server in Rust as they have heard it is more secure.

Find it here: `https://reinterpret.ctf.secso.cc/`

## Hints

1. Check out https://rocket.rs/v0.5-rc/guide/requests/

## Solution

<details>
<summary>Spoiler</summary>

### Idea

A firewall prevents `PATCH` requests, but rocket's "reinterpret" functionality lets
you bypass it.

### Walkthrough

1. Accessing the API shows the routes we can use:

```
{"api":"reinterpret","webserver":"rocket","routes":[{"path":"/flag","method":"PATCH","description":"Outputs the flag"}]}
```

We can see that there is a flag route with method "PATCH".

This means that if we perform a HTTP request with the specified request method `PATCH` we should be able to activate this
route and get the flag.

2. We can access the route with `curl -X PATCH https://reinterpret.ctf.secso.cc/flag`, but this gives us the error:

```
Your request was blocked by the application firewall. "PATCH" requests are not allowed by order of the alien
authorities.
```

This means we need a way to convince the firewall to think we are NOT doing a `PATCH` request, but convince the
application that we ARE.

3. After some research we find that "rocket" is a rust webserver and this [page](https://rocket.rs/v0.5-rc/guide/requests/)
   tells us that we can change the request method in another way:

> Because web browsers only support submitting HTML forms as GET or POST requests, Rocket reinterprets request methods under certain conditions. If a POST request contains a body of Content-Type: application/x-www-form-urlencoded and the form's first field has the name \_method and a valid HTTP method name as its value (such as "PUT"), that field's value is used as the method for the incoming request. This allows Rocket applications to submit non-POST forms. The todo example makes use of this feature to submit PUT and DELETE requests from a web form.

4. We can implement this using a curl command: `curl -H 'Content-Type: application/x-www-form-urlencoded' -d '_method=PATCH' https://reinterpret.ctf.secso.cc/flag` which gives us the flag (as the firewall does not account for reinterpreting methods)

### Flag

`BEGINNER{ru5t_15_certainly_an_1nt3r3sting_langu4g3}`

</details>
