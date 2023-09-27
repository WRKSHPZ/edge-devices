## Azure backend service
This service is an Azure Function app that retrieves the status of a build using a Personal Access Token (PAT). Using a PAT is not a best practice for production scenarios, but really suitable for demos.  

We do not recommend using the workshop time to deploy these resources yourself, because you are fine using the already provided function with the same result.

The function retrieves the status of the latest build and returns 'OK' when ok and 'NOK' when not ok.

If you at any point in time want to recreate this service, feel free to use this as a starting point:

``` 
using System;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using System.Collections.Generic;
using System.Net.Http.Headers;
using System.Net.Http;
using System.Text.Json.Serialization;
using System.Linq;
using System.Text.Json;

namespace WRKSHP.Build.Status
{
    public static class GetBuildStatus
    {
        [FunctionName("GetBuildStatus")]
        public static async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Function, "get", "post", Route = null)] HttpRequest req,
            ILogger log)
        {
            var apiResponseOK = await GetLastBuildStatus(log);

            var responseMessage = apiResponseOK
                ? "OK"
                : "NOK";

            return new OkObjectResult(responseMessage);
        }

        private static async Task<bool> GetLastBuildStatus(ILogger log)
        {
            using var client = new HttpClient();

            // Add an Accept header for JSON format.
            client.DefaultRequestHeaders.Accept.Add(
               new MediaTypeWithQualityHeaderValue("application/json"));

            client.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Basic",
                Convert.ToBase64String(
                    System.Text.ASCIIEncoding.ASCII.GetBytes(
                        string.Format("{0}:{1}", "", "[INSERT_AZURE_DEVOPS_PERSONAL_ACCESS_TOKEN_HERE]"))));

            // Get data response
            var response = await client.GetAsync("[INSERT_AZURE_DEVOPS_API_ENDPOINT_HERE]");

            if (response.IsSuccessStatusCode)
            {
                log.LogInformation(response.StatusCode.ToString());

                // Parse the response body
                var buildStatus = await response.Content.ReadAsAsync<BuildStatusResult>();

                log.LogInformation(JsonSerializer.Serialize(buildStatus));

                var lastBuild = buildStatus?.value?.OrderByDescending(b => b.startTime).FirstOrDefault();

                if (lastBuild == null) {
                    throw new InvalidOperationException("Build could not be retrieved");              
                } else
                {
                    return lastBuild.Result.ToLowerInvariant() != "failed";
                }

            }
            else
            {
                return false;
            }
        }
    }

    public class BuildStatusResult
    {
        [JsonPropertyName("count")]
        public int count { get; set; }

        [JsonPropertyName("value")]
        public List<BuildStatus> value { get; set; }
    }

    public class BuildStatus
    {
        [JsonPropertyName("buildNumber")]
        public string BuildNumber { get; set; }
        [JsonPropertyName("status")]
        public string Status { get; set; }
        [JsonPropertyName("result")]
        public string Result { get; set; }

        public Links _links { get; set; }
        public Properties properties { get; set; }
        public List<object> tags { get; set; }
        public List<object> validationResults { get; set; }
        public List<Plan> plans { get; set; }
        public TriggerInfo triggerInfo { get; set; }
        public int id { get; set; }
        public DateTime queueTime { get; set; }
        public DateTime startTime { get; set; }
        public DateTime finishTime { get; set; }
        public string url { get; set; }
        public Definition definition { get; set; }
        public int buildNumberRevision { get; set; }
        public Project project { get; set; }
        public string uri { get; set; }
        public string sourceBranch { get; set; }
        public string sourceVersion { get; set; }
        public Queue queue { get; set; }
        public string priority { get; set; }
        public string reason { get; set; }
        public RequestedFor requestedFor { get; set; }
        public RequestedBy requestedBy { get; set; }
        public DateTime lastChangedDate { get; set; }
        public LastChangedBy lastChangedBy { get; set; }
        public OrchestrationPlan orchestrationPlan { get; set; }
        public Logs logs { get; set; }
        public Repository repository { get; set; }
        public bool retainedByRelease { get; set; }
        public object triggeredByBuild { get; set; }
        public bool appendCommitMessageToRunName { get; set; }

    }


    public class Avatar
    {
        public string href { get; set; }
    }

    public class Badge
    {
        public string href { get; set; }
    }

    public class Definition
    {
        public List<object> drafts { get; set; }
        public int id { get; set; }
        public string name { get; set; }
        public string url { get; set; }
        public string uri { get; set; }
        public string path { get; set; }
        public string type { get; set; }
        public string queueStatus { get; set; }
        public int revision { get; set; }
        public Project project { get; set; }
    }

    public class LastChangedBy
    {
        public string displayName { get; set; }
        public string url { get; set; }
        public Links _links { get; set; }
        public string id { get; set; }
        public string uniqueName { get; set; }
        public string imageUrl { get; set; }
        public string descriptor { get; set; }
    }

    public class Links
    {
        public Self self { get; set; }
        public Web web { get; set; }
        public SourceVersionDisplayUri sourceVersionDisplayUri { get; set; }
        public Timeline timeline { get; set; }
        public Badge badge { get; set; }
        public Avatar avatar { get; set; }
    }

    public class Logs
    {
        public int id { get; set; }
        public string type { get; set; }
        public string url { get; set; }
    }

    public class OrchestrationPlan
    {
        public string planId { get; set; }
    }

    public class Plan
    {
        public string planId { get; set; }
    }

    public class Pool
    {
        public int id { get; set; }
        public string name { get; set; }
        public bool isHosted { get; set; }
    }

    public class Project
    {
        public string id { get; set; }
        public string name { get; set; }
        public string url { get; set; }
        public string state { get; set; }
        public int revision { get; set; }
        public string visibility { get; set; }
        public DateTime lastUpdateTime { get; set; }
    }

    public class Properties
    {
    }

    public class Queue
    {
        public int id { get; set; }
        public string name { get; set; }
        public Pool pool { get; set; }
    }

    public class Repository
    {
        public string id { get; set; }
        public string type { get; set; }
        public string name { get; set; }
        public string url { get; set; }
        public object clean { get; set; }
        public bool checkoutSubmodules { get; set; }
    }

    public class RequestedBy
    {
        public string displayName { get; set; }
        public string url { get; set; }
        public Links _links { get; set; }
        public string id { get; set; }
        public string uniqueName { get; set; }
        public string imageUrl { get; set; }
        public string descriptor { get; set; }
    }

    public class RequestedFor
    {
        public string displayName { get; set; }
        public string url { get; set; }
        public Links _links { get; set; }
        public string id { get; set; }
        public string uniqueName { get; set; }
        public string imageUrl { get; set; }
        public string descriptor { get; set; }
    }

    public class Self
    {
        public string href { get; set; }
    }

    public class SourceVersionDisplayUri
    {
        public string href { get; set; }
    }

    public class Timeline
    {
        public string href { get; set; }
    }

    public class TriggerInfo
    {
        [JsonPropertyName("ci.sourceBranch")]
        public string cisourceBranch { get; set; }

        [JsonPropertyName("ci.sourceSha")]
        public string cisourceSha { get; set; }

        [JsonPropertyName("ci.message")]
        public string cimessage { get; set; }
    }


    public class Web
    {
        public string href { get; set; }
    }
}

```