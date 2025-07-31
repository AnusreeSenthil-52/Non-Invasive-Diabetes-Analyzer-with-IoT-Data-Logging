(function () {
  emailjs.init("foQHY4rXUirym-hLM"); // Replace with your EmailJS public key
})();

document.getElementById("breathForm").addEventListener("submit", function (e) {
  e.preventDefault();

  const params = {
    name: document.getElementById("name").value,
    age: document.getElementById("age").value,
    gender: document.getElementById("gender").value,
    acetone: document.getElementById("acetone").value,
    result: document.getElementById("result").value,
  };

  emailjs.send("service_sy6ahel", "template_paiss7n", params)
    .then(function (res) {
      document.getElementById("statusMsg").innerText = "✅ Email sent successfully!";
      document.getElementById("breathForm").reset();
    })
    .catch(function (err) {
      document.getElementById("statusMsg").innerText = "❌ Email failed to send.";
      console.error("EmailJS Error:", err);
    });
});
