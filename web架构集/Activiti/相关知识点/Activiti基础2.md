# 简介

[上一章](https://www.jianshu.com/p/aadbfd0e37b0)咱们把环境和数据库搞定了，这章就说下怎么新建一个审批模板，怎么部署模板，怎么发起一个审批任务，怎么删除审批模板怎么查看待审批任务列表。

# 新建审批模板

比如我们需要报销，提交一个申请，然后提交给领导审批，审批完毕后，报销就算结束了。
 流程图如下

 

![img](//upload-images.jianshu.io/upload_images/16004177-e13cbb095bbddaa6.png?imageMogr2/auto-orient/strip|imageView2/2/w/688/format/webp)

image.png

```
<?xml version="1.0" encoding="UTF-8"?>
<definitions xmlns="http://www.omg.org/spec/BPMN/20100524/MODEL" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:activiti="http://activiti.org/bpmn" xmlns:bpmndi="http://www.omg.org/spec/BPMN/20100524/DI" xmlns:omgdc="http://www.omg.org/spec/DD/20100524/DC" xmlns:omgdi="http://www.omg.org/spec/DD/20100524/DI" typeLanguage="http://www.w3.org/2001/XMLSchema" expressionLanguage="http://www.w3.org/1999/XPath" targetNamespace="http://www.activiti.org/test">
  <process id="firstProcess" name="firstProcess" isExecutable="true">
    <startEvent id="start" name="Start"></startEvent>
    <sequenceFlow id="flow1" sourceRef="start" targetRef="apply"></sequenceFlow>
    <userTask id="t1" name="经理审核" activiti:candidateGroups="jl"></userTask>
    <sequenceFlow id="flow2" sourceRef="apply" targetRef="t1"></sequenceFlow>
    <userTask id="apply" name="提交申请" activiti:assignee="${userId}"></userTask>
    <sequenceFlow id="flow3" sourceRef="t1" targetRef="exclusivegateway2"></sequenceFlow>
    <exclusiveGateway id="exclusivegateway2" name="排他网关判断"></exclusiveGateway>
    <userTask id="t2" name="总监审批" activiti:candidateGroups="zj"></userTask>
    <sequenceFlow id="flow4" sourceRef="exclusivegateway2" targetRef="t2"></sequenceFlow>
    <userTask id="t3" name="管理员审核" activiti:candidateGroups="gly"></userTask>
    <sequenceFlow id="flow5" sourceRef="exclusivegateway2" targetRef="t3"></sequenceFlow>
    <endEvent id="end" name="End"></endEvent>
    <sequenceFlow id="flow6" sourceRef="t2" targetRef="end"></sequenceFlow>
    <sequenceFlow id="flow7" sourceRef="t3" targetRef="end"></sequenceFlow>
  </process>
  <bpmndi:BPMNDiagram id="BPMNDiagram_firstProcess">
    <bpmndi:BPMNPlane bpmnElement="firstProcess" id="BPMNPlane_firstProcess">
      <bpmndi:BPMNShape bpmnElement="start" id="BPMNShape_start">
        <omgdc:Bounds height="35.0" width="35.0" x="280.0" y="140.0"></omgdc:Bounds>
      </bpmndi:BPMNShape>
      <bpmndi:BPMNShape bpmnElement="t1" id="BPMNShape_t1">
        <omgdc:Bounds height="55.0" width="105.0" x="510.0" y="130.0"></omgdc:Bounds>
      </bpmndi:BPMNShape>
      <bpmndi:BPMNShape bpmnElement="apply" id="BPMNShape_apply">
        <omgdc:Bounds height="55.0" width="105.0" x="360.0" y="130.0"></omgdc:Bounds>
      </bpmndi:BPMNShape>
      <bpmndi:BPMNShape bpmnElement="exclusivegateway2" id="BPMNShape_exclusivegateway2">
        <omgdc:Bounds height="40.0" width="40.0" x="660.0" y="138.0"></omgdc:Bounds>
      </bpmndi:BPMNShape>
      <bpmndi:BPMNShape bpmnElement="t2" id="BPMNShape_t2">
        <omgdc:Bounds height="55.0" width="105.0" x="745.0" y="131.0"></omgdc:Bounds>
      </bpmndi:BPMNShape>
      <bpmndi:BPMNShape bpmnElement="t3" id="BPMNShape_t3">
        <omgdc:Bounds height="55.0" width="105.0" x="745.0" y="30.0"></omgdc:Bounds>
      </bpmndi:BPMNShape>
      <bpmndi:BPMNShape bpmnElement="end" id="BPMNShape_end">
        <omgdc:Bounds height="35.0" width="35.0" x="895.0" y="141.0"></omgdc:Bounds>
      </bpmndi:BPMNShape>
      <bpmndi:BPMNEdge bpmnElement="flow1" id="BPMNEdge_flow1">
        <omgdi:waypoint x="315.0" y="157.0"></omgdi:waypoint>
        <omgdi:waypoint x="360.0" y="157.0"></omgdi:waypoint>
      </bpmndi:BPMNEdge>
      <bpmndi:BPMNEdge bpmnElement="flow2" id="BPMNEdge_flow2">
        <omgdi:waypoint x="465.0" y="157.0"></omgdi:waypoint>
        <omgdi:waypoint x="510.0" y="157.0"></omgdi:waypoint>
      </bpmndi:BPMNEdge>
      <bpmndi:BPMNEdge bpmnElement="flow3" id="BPMNEdge_flow3">
        <omgdi:waypoint x="615.0" y="157.0"></omgdi:waypoint>
        <omgdi:waypoint x="660.0" y="158.0"></omgdi:waypoint>
      </bpmndi:BPMNEdge>
      <bpmndi:BPMNEdge bpmnElement="flow4" id="BPMNEdge_flow4">
        <omgdi:waypoint x="700.0" y="158.0"></omgdi:waypoint>
        <omgdi:waypoint x="745.0" y="158.0"></omgdi:waypoint>
      </bpmndi:BPMNEdge>
      <bpmndi:BPMNEdge bpmnElement="flow5" id="BPMNEdge_flow5">
        <omgdi:waypoint x="680.0" y="138.0"></omgdi:waypoint>
        <omgdi:waypoint x="680.0" y="57.0"></omgdi:waypoint>
        <omgdi:waypoint x="745.0" y="57.0"></omgdi:waypoint>
      </bpmndi:BPMNEdge>
      <bpmndi:BPMNEdge bpmnElement="flow6" id="BPMNEdge_flow6">
        <omgdi:waypoint x="850.0" y="158.0"></omgdi:waypoint>
        <omgdi:waypoint x="895.0" y="158.0"></omgdi:waypoint>
      </bpmndi:BPMNEdge>
      <bpmndi:BPMNEdge bpmnElement="flow7" id="BPMNEdge_flow7">
        <omgdi:waypoint x="850.0" y="57.0"></omgdi:waypoint>
        <omgdi:waypoint x="912.0" y="57.0"></omgdi:waypoint>
        <omgdi:waypoint x="912.0" y="141.0"></omgdi:waypoint>
      </bpmndi:BPMNEdge>
    </bpmndi:BPMNPlane>
  </bpmndi:BPMNDiagram>
</definitions>
```

# 设置审批模板属性

```
package com.glj.activiti.config;

import lombok.extern.log4j.Log4j2;
import org.activiti.spring.SpringProcessEngineConfiguration;
import org.activiti.spring.boot.ProcessEngineConfigurationConfigurer;
import org.springframework.stereotype.Component;

@Log4j2
@Component
public class ShareniuProcessEngineConfigurationConfigurer implements ProcessEngineConfigurationConfigurer  {
    public void configure(SpringProcessEngineConfiguration processEngineConfiguration) {
        processEngineConfiguration.setActivityFontName("宋体");
        processEngineConfiguration.setAnnotationFontName("宋体");
        processEngineConfiguration.setActivityFontName("宋体");
        log.info("ShareniuProcessEngineConfigurationConfigurer配置的字体#############"+processEngineConfiguration.getActivityFontName());
    }
}
```

# 部署流程

为了使我们的流程被Activiti Engine所知，我们需要部署该流程

```
package com.glj.activiti.controller;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.stream.Collectors;

import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.activiti.engine.RuntimeService;
import org.activiti.engine.TaskService;
import org.activiti.engine.impl.identity.Authentication;
import org.activiti.engine.task.Task;
import org.activiti.engine.task.TaskQuery;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RequestPart;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import com.glj.activiti.enums.ResponseCode;
import com.glj.activiti.dto.AuditAddUserRequest;
import com.glj.activiti.dto.StartProcessRequest;
import com.glj.activiti.response.JsonResult;
import com.glj.activiti.response.TaskResponse;
import com.glj.activiti.service.IGroupService;
import com.glj.activiti.service.IProcDefService;
import com.glj.activiti.service.IUserService;
import com.glj.activiti.vo.Group;
import com.glj.activiti.vo.User;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import lombok.val;
import lombok.extern.slf4j.Slf4j;


@RestController
@Slf4j
@RequestMapping("/taskController")
public class TaskController {
    
    @Autowired
    private RuntimeService runtimeService;
    @Autowired
    private IUserService userService;
    @Autowired
    private TaskService taskService;
    @Autowired
    private IProcDefService procDefService;
    @Autowired
    private IGroupService groupservice;
    
    
     @ApiOperation(value ="部署流程",notes = "添加用户申请的审核处理")
     @PostMapping(value ="/deployProcess") 
    public JsonResult deployProcess(@RequestParam("tenantId") String tenantId, @RequestParam(name="category") String category,
            @RequestParam(name="fileName") String fileName, @RequestPart("file") MultipartFile file) {
        return procDefService.deployProcDef(category, file, tenantId, fileName);
    }
}
```

部署类型为zip，bar，png，bmmn

```
@Override
    public JsonResult deployProcDef(String category, MultipartFile file, String tenantId, String fileName) {
        LOGGER.info("deploy(category={}, file={}, tenantId={}, name={})", category, file.getName(), tenantId, fileName);

        InputStream fileInputStream = null;
        JsonResult result = new JsonResult();
        try {
            fileInputStream = file.getInputStream();
        } catch (IOException e) { 
             result.setCode(ResponseCode.ERROR.getValue()).setErrMsg(e.getMessage());
        }
        Deployment deployment = null;
        String basename = FilenameUtils.getBaseName(fileName);
        String extension = FilenameUtils.getExtension(fileName);
        if (extension.equals("zip") || extension.equals("bar")) {
            ZipInputStream zip = new ZipInputStream(fileInputStream);
            deployment = this.repositoryService.createDeployment().name(basename).category(category).tenantId(tenantId)
                    .addZipInputStream(zip).deploy();
        } else if (extension.equals("png")) {
            deployment = this.repositoryService.createDeployment().category(category).tenantId(tenantId).name(file.getName())
                    .addInputStream(fileName, fileInputStream).deploy();
        } else if (fileName.indexOf("bpmn20.xml") != -1) {
            deployment = this.repositoryService.createDeployment().name(basename).category(category).tenantId(tenantId)
                    .addInputStream(fileName, fileInputStream).deploy();
        } else if (extension.equals("bpmn")) { // bpmn扩展名特殊处理，转换为bpmn20.xml
            String baseName = FilenameUtils.getBaseName(fileName);
            deployment = this.repositoryService.createDeployment().name(basename).category(category).tenantId(tenantId)
                    .addInputStream(baseName + ".bpmn20.xml", fileInputStream).deploy();
        } 

        List<ProcessDefinition> list = repositoryService.createProcessDefinitionQuery()
                .deploymentId(deployment.getId()).list();

        if (CollectionUtils.isEmpty(list)) {
             result.setCode(ResponseCode.ERROR.getValue()).setErrMsg("流程部署失败");
        }else {
             result.setCode("scucess");
                result.setContent(deployment);
        }

        return result;
    }
    
```

部署意味着引擎将解析BPMN流程定义文件并将其转换为可执行文件。此外，还会将记录添加到每个部署的Repository表中。之后，我们可以查询Repository服务从而获取已部署的流程：也就是ProcessDefinitions。

# 发起任务审批

部署完毕后，就可以发起流程了。

```
@ApiOperation(value ="发起任务审批",notes = "发起任务审批")
     @PostMapping(value ="/startProcesses") 
    public JsonResult startProcesses(@RequestBody StartProcessRequest request) {
         JsonResult result = new JsonResult();
        try {
            User user = userService.findUserById(request.getId());
            
            Group currentGroup=groupservice.findGroupById(request.getGroupId());
            
            ConcurrentHashMap<String,Object> variables =new ConcurrentHashMap<String, Object>();
            variables.put("userId",user.getId());
            
            String processId= runtimeService.startProcessInstanceByKeyAndTenantId("firstProcess",variables,request.getTenantId()).getId();
            
            String auditMsg = "管理员";
            // 查询到当前发起人的上一级
            List<Group> groupList = groupservice.findGroupByType( currentGroup.getType()+1);
            if(groupList!=null&&groupList.size()>0){
                auditMsg= groupList.get(0).getName();
            }
            
            log.info("***************发起审批申请开始***************");
            List<Task> tasks = taskService.createTaskQuery().taskAssignee(user.getId()).list();
            log.info("待处理任务数:"+tasks.size());
            for (Task task : tasks) {
                    log.info(user.getId() + "的任务taskname:" + task.getName() + ",id:" + task.getId());
                    taskService.setVariable(task.getId(), "msg", auditMsg);//设置审批类型
                    taskService.complete(task.getId());//完成任务
                    log.info("需要做的下一步审批:" + "审批意见");
            }
            log.info("***************提交添加用户申请完成***************");
            
            
            user.setState(0);
            //修改状态
            user.setAuditState("审核中");
            user.setProcessId(processId);
            
            user = userService.updateState(user);
            
            if(user!=null){
                  result.setCode(ResponseCode.SUCCESS.getValue());
            }else{
                result.setCode(ResponseCode.ERROR.getValue()).setErrMsg("添加用户失败");
            }
        } catch (Exception e) {
             log.error(e.getMessage());
             result.setCode(ResponseCode.ERROR.getValue()).setErrMsg(e.getMessage());
        }
        
        return result;
    }
```

# 获取待办任务列表

```
  @ApiOperation(value ="获取流程待办任务列表",notes = "分页展示流程待办任务基础信息")
        @PostMapping(value ="/todoList}")
        public JsonResult todoList(@RequestBody StartProcessRequest request){
            JsonResult result = new JsonResult();
           
            //取出用户，角色信息
            Group currentGroup=groupservice.findGroupById(request.getGroupId());

            TaskQuery query = taskService.createTaskQuery().taskCandidateGroup(currentGroup.getId());
            
            // 通过人取审批列表
//          query = this.taskService.createTaskQuery().taskAssignee(request.getId()).active()
//                  .includeProcessVariables().orderByTaskCreateTime().desc();
        
            List<Task> list =query.list();
            List<TaskResponse> responses =new ArrayList<TaskResponse>();
           for (Task task : list) {
               TaskResponse response =new TaskResponse();
               BeanUtils.copyProperties(task,response);
               responses.add(response);
           }
            result.setCode(ResponseCode.SUCCESS.getValue()).setContent(responses);
            return result;
        }
```

# 审批人审核任务

```
@ApiOperation(value ="待办任务处理审核",notes = "添加用户申请的审核处理")
    @PostMapping(value ="/audit/add_user")
    public JsonResult auditAddUser(@RequestBody AuditAddUserRequest auditAddUserRequest) {
        JsonResult result = new JsonResult();
        try {
          
            //首先根据ID查询任务
            Task task=taskService.createTaskQuery() // 创建任务查询
                    .taskId(auditAddUserRequest.getTaskId()) // 根据任务id查询
                    .singleResult();
            Map<String,Object> variables=new HashMap<String,Object>();
            
            // 取用户信息,更新审核状态
            String userId=(String) taskService.getVariable(auditAddUserRequest.getTaskId(), "userId");
            User user=userService.findUserById(userId);
            Group currentGroup=groupservice.findGroupById(user.getGroupIds());
            
            if(auditAddUserRequest.getState()==1){
                user.setAuditState("审核通过");
                user.setState(1);
                variables.put("msg", "通过");
            }else{
                user.setAuditState("审核未通过");
                user.setState(-1);
                variables.put("msg", "未通过");
            }
            // 更新审核信息
            userService.updateState(user);

            // 获取流程实例id
            String processInstanceId=task.getProcessInstanceId();
          
            // 添加批注信息
            taskService.addComment(auditAddUserRequest.getTaskId(), processInstanceId, auditAddUserRequest.getComment());
            
            // 设置用户id
            Authentication.setAuthenticatedUserId(user.getFirst()+user.getLast()+"["+currentGroup.getName()+"]");
            
            // 完成任务
            taskService.complete(auditAddUserRequest.getTaskId(), variables);

            result.setCode(ResponseCode.SUCCESS.getValue());
        }catch (Exception e){
             log.error(e.getMessage());
             result.setCode(ResponseCode.ERROR.getValue()).setErrMsg(e.getMessage());
        }
       
        return result;
    }
```

# 删除流程

该流程肯能后期需要添加审批节点或者修改审批规则，需要提前进行删除，然后再次进行部署

```
     @ApiOperation(value ="删除流程",notes = "删除流程")
     @PostMapping(value ="/deleteDeployment") 
    public JsonResult deployProcess(@RequestParam("deploymentId") String deploymentId) {
        return procDefService.deleteDeployment(deploymentId);
    }
     
```

```
    @Override
    public JsonResult deleteDeployment(String deploymentId) {
        JsonResult result = new JsonResult();
        LOGGER.info("deleteDeployment(deploymentId={})", deploymentId);
        
        Deployment deployment = repositoryService.createDeploymentQuery().deploymentId(deploymentId).singleResult();
        if (deployment == null ) {
            result.setCode(ResponseCode.ERROR.getValue()).setErrMsg("流程部署id:" + deploymentId + " 不存在");
        }else {
            repositoryService.deleteDeployment(deploymentId, true);
            result.setCode(ResponseCode.SUCCESS.getValue()).setContent("流程部署id:" + deploymentId + " 删除成功");
        }
        
        return result;
    }
```

# 暂停和激活流程

我们可以暂停ProcessDefinition和ProcessInstance。如果我们暂停一个流程定义ProcessDefinition，则在它暂停挂起时我们就无法创建它的实例。我们可以使用RepositoryService来做到这一点：

```
@Test(expected = ActivitiException.class)
public void givenDeployedProcess_whenSuspend_thenNoProcessInstance() {
   // deploy the process definition
   repositoryService.suspendProcessDefinitionByKey("vacationRequest");
   runtimeService.startProcessInstanceByKey("vacationRequest");
}
要再次激活它，我们只需要调用其中一个repositoryService.activateProcessDefinitionXXX方法。
```

同样，我们可以使用RuntimeService暂停ProcessInstance

# 获取下一个环节列表

```
@ApiOperation("获取下一环节列表")
    @RequestMapping(value = "/next/list", method = RequestMethod.POST)
    public List<PvmActivityResponse> nextTask(@RequestBody PvmActivityRequest request) {
        log.info("nextActivity(request={})", request);
        List<PvmActivity> pvmActivityList = Lists.newArrayList();

        // 根据流程ID获取下一向前的节点
        if (org.apache.commons.lang3.StringUtils.isNotBlank(request.getProcInsId())) {
            // 根据流程实例ID查询任务
            List<Task> tasks = taskService.createTaskQuery().processInstanceId(request.getProcInsId()).list();
            
            if (!tasks.isEmpty()) {
                for (Task task : tasks) {
                    // 根据当前任务获取当前流程的流程定义，然后根据流程定义获得所有的节点：
                    ProcessDefinitionEntity processDefinition = (ProcessDefinitionEntity) ((RepositoryServiceImpl) this.repositoryService)
                            .getDeployedProcessDefinition(task.getProcessDefinitionId());
                    List<ActivityImpl> activitiList = processDefinition.getActivities();
                    // 根据任务获取当前流程执行ID，执行实例以及当前流程节点的ID：
                    Execution execution = this.runtimeService.createExecutionQuery().executionId(task.getExecutionId()).singleResult();//根据ID获取执行器
                    String activitiId = execution.getActivityId();
                    // 循环activitiList 并判断出当前流程所处节点，然后得到当前节点实例，根据节点实例获取所有从当前节点出发的路径，然后根据路径获得下一个节点实例：
                    if (!activitiList.isEmpty()) {
                        for (ActivityImpl activityImpl : activitiList) {
                            if (activitiId.equals(activityImpl.getId())) {
                                List<PvmTransition> outTransitions = activityImpl.getOutgoingTransitions();// 获取从某个节点出来的所有线路
                                recursiveSelect(pvmActivityList, outTransitions,
                                        ArrayUtils.toArray(ProcessConstant.ACTIVITY_TYPE_USERTASK, ProcessConstant.ACTIVITY_TYPE_ENDEVENT));
                                break;
                            }
                        }
                    }
                }
            }
        } else if (org.apache.commons.lang3.StringUtils.isNotBlank(request.getTenantId()) && org.apache.commons.lang3.StringUtils.isNotBlank(request.getProcDefKey())) {
            // 根据tenantId和流程定义key查找开始用户节点
            ProcessDefinition processDefinition = this.repositoryQuery
                    .getLatestProcDefByKeyAndTenantId(request.getProcDefKey(), request.getTenantId());
            if (processDefinition != null) {
                ProcessDefinitionEntity processDefinitionEntity = this.repositoryQuery
                        .getProcDefEntity(processDefinition.getId());
                List<ActivityImpl> activitiList = processDefinitionEntity.getActivities();
                if (activitiList.isEmpty()) {
                    // 找到开始节点
                    ActivityImpl startEvent = null;
                    for (ActivityImpl activityImpl : activitiList) {
                        if (ProcessConstant.ACTIVITY_TYPE_STARTEVENT.equalsIgnoreCase(
                                activityImpl.getProperty("type").toString())) {
                            startEvent = activityImpl;
                            break;
                        }
                    }

                    // 找到开始节点后的第一个用户节点
                    if (startEvent != null) {
                        List<PvmTransition> outTransitions = startEvent.getOutgoingTransitions();// 获取从某个节点出来的所有线路
                        recursiveSelect(pvmActivityList, outTransitions,
                                ProcessConstant.ACTIVITY_TYPE_USERTASK);
                    }
                }
            }
        }

        List<PvmActivityResponse> list = Lists.newArrayList();
        if (!pvmActivityList.isEmpty()) {
            list = pvmActivityList.stream().map(activityFunction).collect(Collectors.toList());
        }

        return list;
    }
    
    
    
    /**
         * 递归获取指定类型的节点
     *
     * @param pvmActivityList
     * @param outTransitions
     * @param types
     * @return
     */
    public static List<PvmActivity> recursiveSelect(List<PvmActivity> pvmActivityList,
                                                    List<PvmTransition> outTransitions, String... types) {
        if (!outTransitions.isEmpty()) {
            for (PvmTransition pvmTransition : outTransitions) {
                // 根据流程线的condition过滤驳回的环节，如果包含back则跳过指向流程
                Object conditionText = pvmTransition.getProperty("conditionText");
                if (conditionText != null
                        && conditionText.toString().equalsIgnoreCase(ProcessConstant.TASK_STATUS_BACK)) {
                    continue;
                }

                PvmActivity pvmActivity = pvmTransition.getDestination();
                Object typeObj = pvmActivity.getProperty("type");
                if (typeObj != null) {
                    if (ArrayUtils.contains(types, typeObj.toString())) {
                        pvmActivityList.add(pvmActivity);
                    } else {
                        recursiveSelect(pvmActivityList, pvmActivity.getOutgoingTransitions(), types);
                    }
                }
            }
        }
        return pvmActivityList;
    }
```

# 获取下一环节用户列表

```
 /**
     * 获取下一环节用户列表
     * @param request
     * @return
     */
  
    public List<UserResponse> listUserByActId(ActivityUserRequest request) {
        log.info("listUserByActId(request={})", request);
        final List<UserResponse> response = Lists.newArrayList();

        ProcessDefinition processDefinition = this.repositoryQuery.getProcDefById(request.getProcDefId());
        Preconditions.checkNotNull(processDefinition,"流程定义ID【" + request.getProcDefId() + "】不存在");

        ProcessDefinitionEntity processDefinitionEntity = (ProcessDefinitionEntity) ((RepositoryServiceImpl) this.repositoryService)
                .getDeployedProcessDefinition(processDefinition.getId());
        List<ActivityImpl> activitiList = processDefinitionEntity.getActivities();

        if (!activitiList.isEmpty()) {
            List<ActivityImpl> filterList = activitiList.stream()
                    .filter(activity -> request.getActivityId().equals(activity.getId()))
                    .collect(Collectors.toList());

            
            Preconditions.checkNotNull(filterList,"节点ID【" + request.getActivityId() + "】不存在");

            ActivityImpl activity = filterList.get(0);
            ActivityBehavior activityBehavior = activity.getActivityBehavior();
            // 检查是否用户任务
            boolean result = activityBehavior instanceof UserTaskActivityBehavior;
            if (!result) {
                 throw new NullPointerException(String.valueOf("节点ID【\" + request.getActivityId() + \"】非用户任务"));
            }
            
            UserTaskActivityBehavior utaBehavior = (UserTaskActivityBehavior) activityBehavior;
            TaskDefinition taskDefinition = ((UserTaskActivityBehavior) utaBehavior).getTaskDefinition();

            // 获取候选用户ID表达式列表
            Set<Expression> userIds = taskDefinition.getCandidateUserIdExpressions();
            if (!userIds.isEmpty()) {
                List<String> users = userIds.stream().map(userId -> {
                    return userId.getExpressionText();
                }).collect(Collectors.toList());

                // 添加指定用户ID列表的用户
                response.addAll(users.stream().map(userInfo->{
                    UserResponse user = new UserResponse();
                    user.setUserId(userInfo);
                    return user;
                }).collect(Collectors.toList()));

                // 添加指定流程变量表达式的用户
                if (org.apache.commons.lang3.StringUtils.isNotBlank(request.getProcInsId())) {
                    users.forEach(user -> {
                        // 流程启动人变量
                        if (user.equals(ProcessConstant.PROCESS_VARIABLES_START_USER_ID)) {
                            String userId = this.runtimeQuery.getProcessStartUser(request.getProcInsId());
                            if (org.apache.commons.lang3.StringUtils.isNotBlank(userId)) {
                                UserResponse user1 = new UserResponse();
                                user1.setUserId(userId);
                                response.add(user1);
                                
                            }
                        }
                    });
                }
            }

            // 获取候选组ID列表
            Set<Expression> groupIds = taskDefinition.getCandidateGroupIdExpressions();
            if (!groupIds.isEmpty()) {
                List<String> groups = groupIds.stream().map(groupId -> {
                    return groupId.getExpressionText();
                }).collect(Collectors.toList());
                // 查找所有该组的用户
                groups.forEach(group -> {
                    GroupUserQueryRequest queryRequest = new GroupUserQueryRequest(request.getTenantId(), group);
                    
                    //response.addAll(this.identityManager.listUserByGroup(queryRequest));
                });

            }
        }

        return response;
    }
```

# 获取流程图图片

```
/**
     * 流程定义Key
     * 流程实例ID
     * 租户主键
     * 获取流程图图片
     * @param request
     * @return
     */
    
    public InputStream tracePhoto(TraceRequest request) {
        log.info("tracePhoto(request={})", request);
        ProcessDefinition processDefinition = this.checkProcDef(request.getProcDefKey(), request.getTenantId());

        List<String> activeActivityIds = Lists.newArrayList();
        if (this.runtimeService.createExecutionQuery().executionId(request.getProcInsId()).count() > 0) {
            activeActivityIds = runtimeService.getActiveActivityIds(request.getProcInsId());
        }

        Context.setProcessEngineConfiguration(this.processEngine.getProcessEngineConfiguration());

        BpmnModel bpmnModel = this.repositoryService.getBpmnModel(processDefinition.getId());
        return new DefaultProcessDiagramGenerator().generateDiagram(bpmnModel, "png", activeActivityIds,
                Collections.<String>emptyList(), this.processEngine.getProcessEngineConfiguration().getActivityFontName(),
                this.processEngine.getProcessEngineConfiguration().getLabelFontName(),
                this.processEngine.getProcessEngineConfiguration().getAnnotationFontName(), null, 1.0);
    }
    /* 检查流程定义 */
    private ProcessDefinition checkProcDef(String procDefKey, String tenantId) {
        ProcessDefinition processDefinition = this.repositoryService.createProcessDefinitionQuery()
                .processDefinitionKey(procDefKey).processDefinitionTenantId(tenantId).latestVersion().active().singleResult();
        if (processDefinition == null) {
             throw new NullPointerException(String.valueOf("流程定义Key:"+ procDefKey + " 不存在"));
        }
        
        return processDefinition;
    }
```

# 获取审批意见列表

```
/**
     * 获取审批意见列表
     * @param procInsId
     * @return
     */
    @Override
    public List<CommentResponse> listComment(String procInsId) {
        log.info("listComment(procInsId={})", procInsId);

        List<CommentResponse> responseList = Lists.newArrayList();
        List<Comment> comments = this.taskService.getProcessInstanceComments(procInsId,
                ProcessConstant.COMMENT_TYPE_COMMENT);
        if (!comments.isEmpty()) {
            comments.forEach(comment -> {
                CommentResponse commentResponse = new CommentResponse();
                CommentEntity commentEntity = (CommentEntity) comment;
                BeanUtils.copyProperties(commentEntity, commentResponse);

                // 没有任务ID则为启动流程，默认状态为true(同意)
                if (org.apache.commons.lang3.StringUtils.isNotBlank(comment.getTaskId())) {
                    
                    HistoricTaskInstance historicTaskInstance = this.historyService.createHistoricTaskInstanceQuery().processInstanceId(procInsId)
                            .taskId(comment.getTaskId()).includeProcessVariables().includeTaskLocalVariables()
                            .finished().singleResult();
                    
                    if (historicTaskInstance != null) {
                        // 有任务ID，则判断任务状态
                        String status = historicTaskInstance.getTaskLocalVariables().get(ProcessConstant.TASK_VARIABLES_DEAL_STATU).toString();
                                
                        if (ProcessConstant.TASK_STATUS_BACK.equals(status)) {
                            commentResponse.setStatus(false);
                        }

                        // 设置任务名称
                        commentResponse.setTaskName(historicTaskInstance.getName());
                    }
                }
                responseList.add(commentResponse);
            });
        }

        // 按最新审批时间排序
        if (!responseList.isEmpty()) {
            Collections.sort(responseList, Comparator.comparing(CommentResponse::getTime).reversed());
        }

        // 获取当前处理人 和 当前节点
        ProcessInstance processInstance = this.runtimeQuery.getActiveProcInst(procInsId);
        if (processInstance != null) {
            CommentResponse commentResponse = new CommentResponse();
            commentResponse.setUserId(ObjectUtils.nullSafeToString(
                    processInstance.getProcessVariables().get(ProcessConstant.PROCESS_VARIABLES_CLAIM)));
            //全局变量 map
            ProcessDefinitionCache.setRepositoryService(repositoryService);
            commentResponse.setTaskName(ProcessDefinitionCache.getActivityName(processInstance.getProcessDefinitionId(),
                    processInstance.getActivityId()));
            commentResponse.setStatus(null);
            responseList.add(0, commentResponse);
        }

        return responseList;
    }
```

# 结束语

到目前位置，Activiti主要的功能已经完成的差不多了,后面还有一些激活流程，或者将流程模板挂起，后续再补充上。

 

 

 原文链接：<https://www.jianshu.com/p/5dadb18469b3> 

 

 